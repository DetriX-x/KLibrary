#include "AdminForm.h"

AdminForm::AdminForm(QWidget *parent, QSqlDatabase* db)
    : BaseUserForm{parent}, _db{db} 
{
    initUi();
    initEntities();
}

void AdminForm::pb_fromLeftSide_toggled(bool isChecked)
{
    if(!isChecked) return; 
    auto e_index = buttonGroup.checkedId();
    ui->rightSide->setCurrentWidget(this->empty);    
    for(auto& e : entities)
    {
        if(e)
        {
            e->clear();
        }
    }
    if(entities[e_index])
    {
        entities[e_index]->select();
    }
}

void AdminForm::on_lineEdit_search_returnPressed()
{
    auto& query = entities[buttonGroup.checkedId()]->getQuery();
    this->search(query);
} 


void AdminForm::on_tableView_clicked(const QModelIndex &index)
{
    int indexRow = index.row();
    rowId = ui->tableView->model()->data(ui->tableView->model()->index(indexRow, 0)).toString();
    QVector<QVariant> data;
    for(int i = 0; i < ui->tableView->model()->columnCount(); ++i)
    {
        data.push_back(ui->tableView->model()->data(ui->tableView->model()->index(indexRow, i)));
    }
    auto e = entities[buttonGroup.checkedId()];
    if(!e) return;
    e->setData(data);
    ui->rightSide->setCurrentWidget(rowInfo);
    rightSideRow->setCurrentWidget(e->form());
} 

void AdminForm::reset() const
{
    BaseUserForm::reset();
    this->buttonGroup.button(0)->click();
    ui->lineEdit_search->setFocus();
}

void AdminForm::pb_ok_clicked()
{
    auto e = entities[buttonGroup.checkedId()];
    if(e->getId()) // update mode
    {
        if(!e->update())
        {
            QMessageBox::warning(this, tr("Error"), tr("Invalid values entered. ") + _db->lastError().text());
            return;
        }
        e->select(_filter);
    }
    else // insert mode
    {
        if(!e->insert())
        {
            QMessageBox::warning(this, tr("Error"), tr("Invalid values entered. ") + _db->lastError().text());
            return;
        }
        e->select(_filter); 
    }
}

void AdminForm::pb_addRow_clicked()
{
    auto e = entities[buttonGroup.checkedId()];
    ui->rightSide->setCurrentWidget(rowInfo);
    rightSideRow->setCurrentWidget(e->form());
    ui->tableView->clearSelection();
    e->clear();
}

void AdminForm::pb_removeRow_clicked()
{
    auto e = entities[buttonGroup.checkedId()];
    ui->tableView->clearSelection();
    if(!e->remove())
    {
        QMessageBox::warning(this, tr("Error"), tr("Specify the line to be deleted"));
        return;
    }
    e->clear();
    e->select(_filter);
    ui->rightSide->setCurrentWidget(empty);
}

void AdminForm::initUi()
{
    ui->label_userImg->setPixmap(QPixmap("../KLibrary/imgs/Admin-64.png"));
    leftSideLayout = qobject_cast<QVBoxLayout*>(ui->leftSide->layout());
    pb_books = new QPushButton;
    pb_books->setIcon(QIcon("../KLibrary/imgs/books-96.png"));
    pb_books->setText(tr("Books"));
    leftSideLayout->addWidget(pb_books, 1);
    QPushButton* pb_authors = new QPushButton;
    pb_authors->setIcon(QIcon("../KLibrary/imgs/author-96.png"));
    pb_authors->setText(tr("Authors"));
    leftSideLayout->addWidget(pb_authors, 1);
    QPushButton* pb_readers = new QPushButton;
    pb_readers->setIcon(QIcon("../KLibrary/imgs/reader-96.png")); 
    pb_readers->setText(tr("Readers"));
    leftSideLayout->addWidget(pb_readers, 1);
    QPushButton* pb_reviews = new QPushButton;
    pb_reviews->setIcon(QIcon("../KLibrary/imgs/review-96.png"));
    pb_reviews->setText(tr("Reviews"));
    leftSideLayout->addWidget(pb_reviews, 1);
    QPushButton* pb_orders = new QPushButton;
    pb_orders->setIcon(QIcon("../KLibrary/imgs/order-96.png"));
    pb_orders->setText(tr("Orders"));
    leftSideLayout->addWidget(pb_orders, 1);
    QPushButton* pb_genres = new QPushButton;
    pb_genres->setIcon(QIcon("../KLibrary/imgs/genre-96.png"));
    pb_genres->setText(tr("Genres"));
    leftSideLayout->addWidget(pb_genres, 1);
    QPushButton* pb_editions = new QPushButton;
    pb_editions->setIcon(QIcon("../KLibrary/imgs/edition-96.png"));
    pb_editions->setText(tr("Editions"));
    leftSideLayout->addWidget(pb_editions, 1);
    buttonGroup.setExclusive(true);
    for(int i = 1; i < leftSideLayout->count(); ++i)
    {
        auto pb = qobject_cast<QPushButton*>(leftSideLayout->itemAt(i)->widget());
        if(!pb) continue;
        pb->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
        pb->setStyleSheet("text-align: left; padding: 6px;");
        pb->setCheckable(true);
        pb->setAutoExclusive(true);
        connect(pb, &QPushButton::toggled, this, &AdminForm::pb_fromLeftSide_toggled);
        buttonGroup.addButton(pb, i - 1);
    }
    leftSideLayout->addStretch(3);
    QHBoxLayout* twoButtons = new QHBoxLayout;
    pb_removeRow = new QPushButton;
    pb_removeRow->setText(tr("Remove"));
    pb_removeRow->setIcon(QIcon("../KLibrary/imgs/remove-64.png"));
    pb_removeRow->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    pb_removeRow->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pb_removeRow->setStyleSheet("text-align: left; padding: 6px;");
    connect(pb_removeRow, &QPushButton::clicked, this, &AdminForm::pb_removeRow_clicked);
    twoButtons->addWidget(pb_removeRow, 1); 
    pb_addRow = new QPushButton;
    pb_addRow->setText(tr("Append"));
    pb_addRow->setIcon(QIcon("../KLibrary/imgs/add-64.png"));
    pb_addRow->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pb_addRow->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    pb_addRow->setStyleSheet("text-align: left; padding: 6px;");
    connect(pb_addRow, &QPushButton::clicked, this, &AdminForm::pb_addRow_clicked);
    twoButtons->addWidget(pb_addRow, 1);
    twoButtons->setSpacing(8);
    auto mainLayout = qobject_cast<QVBoxLayout*>(ui->mainView->layout());
    mainLayout->addLayout(twoButtons, 1);
    mainLayout->setStretch(0, 15);
    // init rightSide
    rowInfo = new QWidget;
    QVBoxLayout* rowInfoLayout = new QVBoxLayout(rowInfo);
    rightSideRow = new QStackedWidget;
    rightSideRow->setStyleSheet("QStackedWidget{background-color: transparent;}");
    pb_ok = new QPushButton;
    pb_ok->setText(tr("Ok"));
    connect(pb_ok, &QPushButton::clicked, this, &AdminForm::pb_ok_clicked);
    rowInfoLayout->addWidget(rightSideRow, 10);
    rowInfoLayout->addWidget(pb_ok);
    ui->rightSide->addWidget(rowInfo);
}

void AdminForm::initEntities()
{
    for(auto& e : entities)
    {
        e = nullptr;
    }

    entities[books] = new Books("V_books", this->model, _db);
    entities[books]->setUserFriendlyFieldNames(QStringList({tr("Book ID"), tr("Title"), tr("Authors"), 
                                                tr("Genre"), tr("Language"), tr("Year"),
                                                tr("Edition"), tr("Quantity")}));
    entities[books]->setTableName("books");
    rightSideRow->addWidget(entities[books]->form());
    entities[reviews] = new Reviews("V_reviews", this->model);
    entities[reviews]->setTableName("reviews");
    entities[reviews]->setUserFriendlyFieldNames(QStringList({tr("Review ID"), tr("Reader ID"),
                                                  tr("Reader login"), tr("Book ID"), 
                                                  tr("Book title"),tr("Rating"),
                                                  tr("Content"), tr("Date")}));
    rightSideRow->addWidget(entities[reviews]->form());

    entities[orders] = new Orders("V_orders", this->model);
    entities[orders]->setTableName("orders");
    entities[orders]->setUserFriendlyFieldNames(QStringList({tr("Order ID"), tr("Reader ID"), tr("Reader Login"),
                                                     tr("Book ID"), tr("Titile"), tr("Date Start"),
                                                     tr("Date End"), tr("Status")}));
    rightSideRow->addWidget(entities[orders]->form());

    entities[authors] = new Authors("authors", this->model);
    entities[authors]->setTableName("authors");
    entities[authors]->setUserFriendlyFieldNames(QStringList({tr("Author ID"), tr("Name"),
                                                     tr("Surname"), tr("Middlename")}));
    rightSideRow->addWidget(entities[authors]->form());
    entities[readers] = new Readers("readers", this->model);
    entities[readers]->setTableName("readers");
    entities[readers]->setUserFriendlyFieldNames(QStringList({tr("Reader ID"), tr("Login"),
                                                     tr("Password"), tr("Phone"), tr("Email")}));
    rightSideRow->addWidget(entities[readers]->form());
    entities[genres] = new Genres("genres", this->model);
    entities[genres]->setTableName("genres");
    entities[genres]->setUserFriendlyFieldNames(QStringList({tr("Genre ID"), tr("Name")}));
    rightSideRow->addWidget(entities[genres]->form());

    entities[editions] = new Editions("editions", this->model);
    entities[editions]->setTableName("editions");
    entities[editions]->setUserFriendlyFieldNames(QStringList({tr("Edition ID"), tr("Name"), tr("Country")}));
    rightSideRow->addWidget(entities[editions]->form());

    pb_books->setChecked(true); // call pb_fromLeftSide_toggled slot
}
