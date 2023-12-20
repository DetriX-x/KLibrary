#include "Books.h"

Books::Books(const QString& viewName, qModel* model, QSqlDatabase* db) :
    Entity(viewName, model), database{db}
{
    initUi();
    editionNameRelation = new Relation("edition_id", "edition_name", "editions");
    cb_edition->addItems(editionNameRelation->getRelationValues());
    genreNameRelation = new Relation("genre_id", "genre_name", "genres");
    cb_genre->addItems(genreNameRelation->getRelationValues());
    authorNameRelation = new Relation("author_id", "concat", "v_authors");
}


void Books::setData(const Data& dataIn) 
{
    _id = dataIn[Id].toInt();
    QSqlQuery q;
    q.prepare("SELECT * FROM books WHERE book_id = " + QString::number(_id));
    if(!q.exec())
    {
        qDebug() << "Books setData() Error";
        return;
    }
    q.first();

    editionNameRelation->loadComboBox(cb_edition);
    cb_edition->setCurrentIndex(editionNameRelation->getIndexByPrimaryKey(q.value(BookTable::Edition_id).toInt()));

    genreNameRelation->loadComboBox(cb_genre);
    cb_genre->setCurrentIndex(genreNameRelation->getIndexByPrimaryKey(q.value(BookTable::Genre_Id).toInt()));

    lineEdit_isbn->setText(q.value(BookTable::ISBN).toString());
    lineEdit_title->setText(q.value(BookTable::Title).toString());
    lineEdit_lang->setText(q.value(BookTable::Lang).toString());
    sp_year->setValue(q.value(BookTable::Year).toInt());
    sp_quantity->setValue(q.value(BookTable::Quantity).toInt());

    cleanScrollArea();

    q.clear();
    q.prepare("SELECT author_id FROM books_authors WHERE book_id = " + QString::number(_id));
    if(!q.exec())
    {
        qDebug() << "Books setData() Error";
        return;
    }
    for(int i = 0; i < q.size(); ++i)
    {
        q.next();
        createComboBox()->setCurrentIndex(authorNameRelation->getIndexByPrimaryKey(q.value(0).toInt()));
    }
}

bool Books::isSameAuthors()
{
     QVector<int> values;
     for(int i = 0; i < authorsComboboxes->layout()->count(); ++i)
     {
         auto cb = qobject_cast<QComboBox*>(authorsComboboxes->layout()->itemAt(i)->widget());
         if(!cb)
         {
             break; 
         }
         values.push_back(cb->currentIndex()); 
     }
     QSet<int> set(values.begin(), values.end());
     if(values.size() != set.size())
     {
         return true;
     }
     return false;
}

bool Books::update()
{
    if(isSameAuthors())
    {
        return false;
    }

    if(!database->transaction())
    {
        return false;
    }
    if(!Entity::update())
    {
        return false;
    }
    QSqlQuery q;
    q.prepare("DELETE FROM books_authors WHERE book_id = " + QString::number(_id));
    if(!q.exec())
    {
        return false;
    }
    QString insertNewRelations = this->getInsertAuthorsQuery(_id);
    qDebug() << insertNewRelations;
    q.clear();
    q.prepare(insertNewRelations);
    if(!q.exec())
    {
        return false;
    }

    if(!database->commit())
    {
        database->rollback();
        return false;
    }
    return true;
}

int Books::insert()
{
    if(isSameAuthors())
    {
        return false;
    }

    if(!database->transaction())
    {
        qDebug() << "Error of starting transaction";
        return false;
    }
    int id = Entity::insert();
    if(!id)
    {
        return false;
    }

    QSqlQuery q;
    QString insertNewRelations = this->getInsertAuthorsQuery(id);
    qDebug() << insertNewRelations;
    q.prepare(insertNewRelations);
    if(!q.exec())
    {
        return false;
    }
    if(!database->commit())
    {
        database->rollback();
        return false;
    }
    return true;
}

const QString Books::getInsertAuthorsQuery(int book_id)
{
    QString query_text = "INSERT INTO books_authors VALUES ";
    auto layout = qobject_cast<QVBoxLayout*>(authorsComboboxes->layout());
    for(int i = 0; i < layout->count() - 1; ++i)
    {
        auto cb = qobject_cast<QComboBox*>(layout->itemAt(i)->widget());
        if(!cb)
        {
            qDebug() << "Error of casting combobox: " << cb; 
            return "";
        }
        query_text += "(" + QString::number(book_id) + ", "
            + QString::number(authorNameRelation->getPrimaryKeyByIndex(cb->currentIndex()))  + "),";
    }
    return query_text.chopped(1);
}

bool Books::remove()
{
    if(!database->transaction())
    {
        qDebug() << "Error of starting transaction";
        return false;
    }

    int res = Entity::remove();

    if(!database->commit())
    {
        database->rollback();
        return false;
    }
    return true && res;
}

QComboBox* Books::createComboBox()
{
    QComboBox* cb = new QComboBox;
    cb->addItem("NULL");
    cb->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    cb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    cb->addItems(authorNameRelation->getRelationValues());
    connect(cb, &QComboBox::currentIndexChanged, this, &Books::on_cb_null_value);
    qobject_cast<QVBoxLayout*>(authorsComboboxes->layout())->insertWidget(0, cb);
    return cb;
}

void Books::on_pb_add_clicked()
{
    auto layout = qobject_cast<QVBoxLayout*>(authorsComboboxes->layout());
    if(layout->count() < 11)
        layout->insertWidget(layout->count() - 2, createComboBox());
    else
        QMessageBox::warning(this->form(), tr("Warning"), tr("Maximum author count is 10."));
}

void Books::on_cb_null_value(int index)
{
    if(!index)
    {
        qobject_cast<QComboBox*>(sender())->deleteLater();
    }
}

void Books::cleanScrollArea()
{
    for(int i = 0; i < authorsComboboxes->layout()->count(); ++i)
    {
        auto combobox = qobject_cast<QComboBox*>(authorsComboboxes->layout()->itemAt(0)->widget());
        if(combobox)
        {
            delete combobox;
        }
    }
}

const QStringList& Books::getData()
{
    Entity::getData();
    _dataOut[BookTable::Edition_id] = QString::number(editionNameRelation->getPrimaryKeyByIndex(cb_edition->currentIndex()));
    _dataOut[BookTable::ISBN] = lineEdit_isbn->text();
    _dataOut[BookTable::Title] = lineEdit_title->text();
    _dataOut[BookTable::Lang] = lineEdit_lang->text();
    _dataOut[BookTable::Year] = QString::number(sp_year->value());
    _dataOut[BookTable::Genre_Id] = QString::number(genreNameRelation->getPrimaryKeyByIndex(cb_genre->currentIndex()));
    _dataOut[BookTable::Quantity] = QString::number(sp_quantity->value());
    return _dataOut;
}

void Books::clear()
{
    Entity::clear();
    editionNameRelation->loadComboBox(cb_edition);
    genreNameRelation->loadComboBox(cb_genre);
    cb_edition->setCurrentIndex(0);
    cb_genre->setCurrentIndex(0);
    cleanScrollArea();
    lineEdit_isbn->clear();
    lineEdit_lang->clear();
    lineEdit_title->clear();
    sp_quantity->setValue(1);
    sp_year->setValue(QDate::currentDate().year());
}

bool Books::isEmptyValues()
{
     bool isBadVal = false;
     if(!cb_edition->currentIndex())
         isBadVal = true;
     if(!cb_genre->currentIndex())
         isBadVal = true;
     if(lineEdit_title->text().isEmpty())
         isBadVal = true;
     if(lineEdit_isbn->text().isEmpty())
         isBadVal = true;
     if(lineEdit_lang->text().isEmpty())
         isBadVal = true;
     // 0 authors specifyed
     if(authorsComboboxes->layout()->count() == 1)
         isBadVal = true;
     for(int i = 0; i < authorsComboboxes->layout()->count(); ++i)
     {
         auto cb = qobject_cast<QComboBox*>(authorsComboboxes->layout()->itemAt(i)->widget());
         if(!cb)
         {
             break; 
         }
         if(!cb->currentIndex())
         {
             isBadVal = true;
             break;
         }
     }
     return isBadVal;
}

void Books::initUi()
{
    lbl_title = new QLabel(tr("Title"));
    _layout->addWidget(lbl_title, 1);
    lineEdit_title = new QLineEdit;
    lineEdit_title->setMaxLength(64);
    _layout->addWidget(lineEdit_title, 1);
    lbl_genre = new QLabel;
    lbl_genre->setText(tr("Genre"));
    _layout->addWidget(lbl_genre, 1);
    cb_genre = new QComboBox;
    cb_genre->addItem("NULL");
    cb_genre->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    _layout->addWidget(cb_genre, 1);
    lbl_lang = new QLabel;
    lbl_lang->setText(tr("Language"));
    _layout->addWidget(lbl_lang, 1);
    lineEdit_lang = new QLineEdit;
    lineEdit_lang->setMaxLength(4);
    _layout->addWidget(lineEdit_lang, 1);
    lbl_year = new QLabel;
    lbl_year->setText(tr("Year"));
    _layout->addWidget(lbl_year, 1);
    sp_year = new QSpinBox;
    sp_year->setMinimum(1);
    sp_year->setMaximum(3000);
    sp_year->setAlignment(Qt::AlignCenter);
    _layout->addWidget(sp_year, 1);
    lbl_edition = new QLabel;
    lbl_edition->setText(tr("Edition"));
    _layout->addWidget(lbl_edition, 1);
    cb_edition = new QComboBox;
    cb_edition->addItem("NULL");
    cb_edition->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    _layout->addWidget(cb_edition, 1);
    lbl_quantity = new QLabel;
    lbl_quantity->setText(tr("Quantity"));
    _layout->addWidget(lbl_quantity, 1);
    sp_quantity = new QSpinBox;
    sp_quantity->setMinimum(0);
    sp_quantity->setMaximum(10000);
    sp_quantity->setAlignment(Qt::AlignCenter);
    _layout->addWidget(sp_quantity, 1);
    lbl_isbn = new QLabel;
    lbl_isbn->setText(tr("isbn"));
    _layout->addWidget(lbl_isbn, 1);
    lineEdit_isbn = new QLineEdit;
    lineEdit_isbn->setMaxLength(32);
    _layout->addWidget(lineEdit_isbn, 1);
    lbl_authors = new QLabel;
    lbl_authors->setText(tr("Authors"));
    _layout->addWidget(lbl_authors, 1);
    scrollArea = new QScrollArea;
    authorsComboboxes = new QWidget; 
    authorsComboboxes->setObjectName("authors");
    authorsComboboxes->setStyleSheet("#authors{background-color: transparent}");
    authorsComboboxes->setLayout(new QVBoxLayout);
    authorsComboboxes->layout()->setContentsMargins(0, 0, 0, 0);
    scrollArea->setWidget(authorsComboboxes);
    scrollArea->setWidgetResizable(true);
    pb_add = new QPushButton;
    pb_add->setText(tr("Add"));
    pb_add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(pb_add, &QPushButton::clicked, this, &Books::on_pb_add_clicked);
    authorsComboboxes->layout()->addWidget(pb_add);
    _layout->addWidget(scrollArea, 20);

    for(int i = 0; i < _layout->count(); ++i)
    {
        _layout->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
}
