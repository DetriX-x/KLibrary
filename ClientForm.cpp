#include "ClientForm.h"

ClientForm::ClientForm(QWidget *parent)
    : BaseUserForm{parent}
{
    pb_myBooks = new QPushButton(this);
    pb_myBooks->setIcon(QIcon("../KLibrary/imgs/books-96.png"));
    pb_myBooks->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    pb_myBooks->setText(tr("My Books"));
    pb_myBooks->setStyleSheet("text-align: left; padding: 6px;");
    QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(ui->leftSide->layout());
    vLayout->addWidget(pb_myBooks, 2);
    lbl_email = new QLabel(this);
    lbl_email->setText(tr("Email"));
    lbl_email->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    vLayout->addWidget(lbl_email, 2);
    le_email = new QLineEdit(this);
    le_email->setPlaceholderText(tr("Enter email..."));
    le_email->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    vLayout->addWidget(le_email, 2);
    lbl_phone = new QLabel(this);
    lbl_phone->setText(tr("Phone"));
    lbl_phone->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    vLayout->addWidget(lbl_phone, 2);
    le_phone = new QLineEdit(this);
    le_phone->setPlaceholderText(tr("Enter phone..."));
    le_phone->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    vLayout->addWidget(le_phone, 2);
    pb_saveUserInfo = new QPushButton(this);
    pb_saveUserInfo->setText(tr("Save"));
    pb_saveUserInfo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    vLayout->addWidget(pb_saveUserInfo, 2);
    vLayout->setStretch(0, 2);
    vLayout->addStretch(15);
    
    connect(pb_saveUserInfo, &QPushButton::clicked, this, &ClientForm::saveUserInfo);
    connect(pb_myBooks, &QPushButton::clicked, this, &ClientForm::pb_myBooks_clicked);
    checker = new InputChecker(this);
    connect(le_email, &QLineEdit::textChanged, checker, &InputChecker::lineEditEmailChanged);
    connect(le_phone, &QLineEdit::textChanged, checker, &InputChecker::lineEditPhoneChanged);

    model->setQuery("SELECT * FROM V_books WHERE quantity <> 0");
    setViewHeaders(isAllBooksMode);
    ui->tableView->setColumnHidden(0, true);

    book = new QWidget;
    lbl_rating = new QLabel;
    lbl_rating->setText(tr("Rating"));
    lbl_rating->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    bar = new QProgressBar;
    lbl_reviews = new QLabel;
    lbl_reviews->setText(tr("Reviews"));
    lbl_reviews->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    reviews = new QTextEdit;
    reviews->setReadOnly(true);
    lbl_myReview = new QLabel;
    lbl_myReview->setText(tr("My review"));
    lbl_myReview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    myReview = new QTextEdit; 
    connect(myReview, &QTextEdit::textChanged, this, &ClientForm::myReview_textChanged);
    lbl_myGrade = new QLabel;
    lbl_myGrade->setText(tr("My grade"));
    lbl_myGrade->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    myGrade = new QSpinBox;
    myGrade->setMaximum(5);
    myGrade->setMinimum(1);
    myGrade->setAlignment(Qt::AlignCenter);
    QHBoxLayout* gradeLayout = new QHBoxLayout;
    gradeLayout->addWidget(lbl_myGrade, 1);
    gradeLayout->addWidget(myGrade, 1);
    pb_saveReview = new QPushButton;
    pb_saveReview->setText(tr("Save"));
    connect(pb_saveReview, &QPushButton::clicked, this,
            [this](){ this->saveReview(bookId.toInt(), myReview->toPlainText(), myGrade->value()); });
    pb_takeBook = new QPushButton;
    pb_takeBook->setText(tr("Take book"));
    connect(pb_takeBook, &QPushButton::clicked, this, &ClientForm::pb_takeBook_clicked);
    QVBoxLayout* bookLayout = new QVBoxLayout(book);
    bookLayout->addWidget(lbl_rating, 1);
    bookLayout->addWidget(bar, 1);
    bookLayout->addWidget(lbl_reviews, 1);
    bookLayout->addWidget(reviews, 4);
    bookLayout->addWidget(lbl_myReview, 1);
    bookLayout->addWidget(myReview, 3);
    bookLayout->addLayout(gradeLayout, 2);
    bookLayout->addWidget(pb_saveReview, 1);
    bookLayout->addWidget(pb_takeBook, 1);
    bookLayout->setSpacing(5);
    ui->rightSide->addWidget(book);

    orderInfo = new QWidget;
    pb_cancelOrder = new QPushButton;
    pb_cancelOrder->setText("Cancel order");
    connect(pb_cancelOrder, &QPushButton::clicked, this, &ClientForm::pb_cancelOrder_clicked);
    QVBoxLayout* cancelLayout = new QVBoxLayout(orderInfo);
    cancelLayout->addWidget(pb_cancelOrder);

    ui->rightSide->addWidget(orderInfo);
}

void ClientForm::saveUserInfo()
{
    if(!checker->checkLineEdit(le_email, InputType::Email) ||
       !checker->checkLineEdit(le_phone, InputType::Phone))
    {
        QMessageBox::warning(this, tr("Error"), tr("Entered values are incorrect"));
        return;
    }
    QSqlQuery query;
    query.prepare("UPDATE readers SET phone = :newPhone, email = :newEmail WHERE reader_id = " +
                  QString::number(this->userId));
    query.bindValue(":newPhone", le_phone->text());
    query.bindValue(":newEmail", le_email->text());
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    QMessageBox::information(this, tr("Information"), tr("Data successfully saved."));
} 

void ClientForm::leftAnimFinished() 
{
    bool visibility = pb_saveUserInfo->isVisible();
    visibility = !visibility;
    le_email->setVisible(visibility);
    lbl_email->setVisible(visibility);
    le_phone->setVisible(visibility);
    lbl_phone->setVisible(visibility);
    pb_saveUserInfo->setVisible(visibility);
}

void ClientForm::pb_myBooks_clicked()
{
    this->clearSorting();
    ui->rightSide->setCurrentWidget(empty);
    QSqlQuery query;
    if(isAllBooksMode)
    {
        query.prepare("SELECT * FROM V_orders WHERE reader_id = " + QString::number(userId));
        pb_myBooks->setText(tr("All books"));
    }
    else
    {
        query.prepare("SELECT * FROM V_books WHERE quantity <> 0");
        pb_myBooks->setText(tr("My books"));
    }
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error"));
        return;
    }
    this->isAllBooksMode = !this->isAllBooksMode;
    setViewHeaders(this->isAllBooksMode);
    model->setQuery(std::move(query));
}

void ClientForm::setViewHeaders(bool isAllBooksMode) const
{
    if(isAllBooksMode)
    {
        ui->tableView->setColumnHidden(0, true);
        ui->tableView->setColumnHidden(1, false);
        ui->tableView->setColumnHidden(2, false);
        model->setHeaderData(1, Qt::Horizontal, tr("Title"));
        model->setHeaderData(2, Qt::Horizontal, tr("Authors"));
        model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
        model->setHeaderData(4, Qt::Horizontal, tr("Language"));
        model->setHeaderData(5, Qt::Horizontal, tr("Year"));
        model->setHeaderData(6, Qt::Horizontal, tr("Edition"));
        model->setHeaderData(7, Qt::Horizontal, tr("Quantity"));
    }
    else
    {
        ui->tableView->setColumnHidden(0, false);
        ui->tableView->setColumnHidden(1, true);
        ui->tableView->setColumnHidden(2, true);
        model->setHeaderData(0, Qt::Horizontal, tr("Order ID"));
        model->setHeaderData(3, Qt::Horizontal, tr("Book ID"));
        model->setHeaderData(4, Qt::Horizontal, tr("Title"));
        model->setHeaderData(5, Qt::Horizontal, tr("Start Date"));
        model->setHeaderData(6, Qt::Horizontal, tr("End Date"));
        model->setHeaderData(7, Qt::Horizontal, tr("Status"));
    }
}

void ClientForm::on_tableView_clicked(const QModelIndex& index) 
{
    bookId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    if(isAllBooksMode)
    {
        selectBookInfo(bookId);
    }
    else
    {
        orderId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
        bookId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();
        QString status = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 6)).toString();
        if(status == "Not confirmed")
        {
            ui->rightSide->setCurrentWidget(orderInfo);
        }
        else
        {
            ui->rightSide->setCurrentWidget(noInfo);
        }
    } 
}

void ClientForm::selectBookInfo(const QString& bookId) 
{
    clearBookInfo();
    ui->rightSide->setCurrentWidget(book);
    // find out the rating and reviews
    QSqlQuery query;
    query.prepare("SELECT * FROM V_reviews WHERE book_id = "\
                    + bookId + " ORDER BY to_timestamp ASC"); // to_char is a datetime
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    auto [li, sum] = parseReviews(query);
    double res = (double(sum) / double(query.size())) / 5.0 * 100; // 5 is max rating
    bar->setValue(int(res));
    reviews->setText(li.join("\n\n"));
    // check if has active order
    pb_takeBook->setEnabled(!hasActiveOrder(bookId.toInt(), userId));
}

void ClientForm::clearBookInfo() const
{
    bar->setValue(0);
    myGrade->setValue(1);
    reviews->clear();
    myReview->clear();
    pb_takeBook->setEnabled(true);
}


std::pair<QStringList, int> ClientForm::parseReviews(QSqlQuery& query) const
{
    int sum = 0;
    int curRating;
    int curReaderId;
    QString curReview;
    QString curLogin;
    QString curDateTime;
    QStringList li;
    QString fullReview;
    int size = query.size();
    for(int i = 0; i < size; ++i)
    { // parsing every query
        query.next();
        curReaderId = query.value(reviews_res::reader_id).toInt();
        curRating = query.value(reviews_res::rating).toInt();
        curReview = query.value(reviews_res::content).toString();
        curLogin = query.value(reviews_res::login).toString();
        curDateTime = query.value(reviews_res::datetime).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if(curLogin == "") // user had been deleted from database
        {
            curLogin = tr("Unknown reader");
        }
        fullReview = curDateTime + " " + curLogin
             + " " +QString::number(curRating);
        if(!curReview.isEmpty())
        {
            fullReview += ("/5:\n" + curReview);
        }
        else
        {
            fullReview += "/5";
        }
        li.push_back(fullReview);
        if(curReaderId == this->userId)
        {
            myGrade->setValue(curRating);
            myReview->setText(curReview);
        }
        sum += curRating;
    }
    return std::make_pair(li, sum);
}

bool ClientForm::hasActiveOrder(int bookId, int userId) 
{
    QSqlQuery query;
    query.prepare("SELECT * FROM orders WHERE book_id = " + QString::number(bookId) +
                  " AND reader_id = " + QString::number(userId) +
                  " AND (status = \'active\' OR status = \'Not confirmed\')");
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return false;
    }
    if(query.size()) // has order 
    {
        return true;
    }
    return false;
}

void ClientForm::myReview_textChanged()
{
    QString text = myReview->toPlainText();
    if(text.length() > MAX_REVIEW_LEN)
    {
        text.chop(text.length() - MAX_REVIEW_LEN); // cut off at MAX_REVIEW_LEN characters
        myReview->setPlainText(text); // reset text
        QTextCursor cursor = myReview->textCursor();
        cursor.setPosition(myReview->document()->characterCount() - 1);
        myReview->setTextCursor(cursor);
    }
}


void ClientForm::saveReview(int bookId, const QString& text, double rating)
{
    QSqlQuery query;
    query.prepare("INSERT INTO reviews(reader_id, book_id, rating, content, review_datetime) "\
                  "VALUES(:reader_id, :book_id, :rating, :content, :dt) "\
                  "ON CONFLICT ON CONSTRAINT unique_reviews_reader_id_book_id "\
                  "DO "\
                  "UPDATE SET rating = :rating, content = :content, review_datetime = :dt;");
    query.bindValue(":book_id", bookId);
    query.bindValue(":reader_id", userId);
    query.bindValue(":rating", rating);
    query.bindValue(":content", text);
    query.bindValue(":dt", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    this->selectBookInfo(QString::number(bookId));
}

void ClientForm::pb_takeBook_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO orders "\
                  "(reader_id, book_id, date_start, date_end, status) "\
                  "VALUES (:reader_id, :book_id, :date_start, :date_end, :status)");
    query.bindValue(":reader_id", userId);
    query.bindValue(":book_id", bookId);
    query.bindValue(":date_start", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":date_end", QDateTime::currentDateTime().addDays(3).toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":status", "Not confirmed");
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    query.clear();
    query.prepare("UPDATE books SET quantity = quantity - 1 WHERE book_id = " + bookId);
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    on_lineEdit_search_returnPressed();
    this->selectBookInfo(bookId);
}

void ClientForm::pb_cancelOrder_clicked()
{
    ui->rightSide->setCurrentWidget(empty);    
    QSqlQuery query;
    query.prepare("DELETE FROM orders WHERE order_id = " + orderId);
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    query.clear();
    query.prepare("UPDATE books SET quantity = quantity + 1 WHERE book_id = " + bookId);
    if(!query.exec())
    {
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error... Please restart the program"));
        return;
    }
    model->setQuery("SELECT * FROM V_orders WHERE reader_id = " + QString::number(userId));
}

void ClientForm::on_lineEdit_search_returnPressed()
{
    if(isAllBooksMode)
    {
        this->search("SELECT * FROM V_books");
    }
    else
    {
        this->search("SELECT * FROM V_orders WHERE reader_id = " + QString::number(userId));
    }
} 

void ClientForm::reset() const 
{
    BaseUserForm::reset();
    if(!isAllBooksMode)
    {
        this->pb_myBooks->click();
    }
    ui->lineEdit_search->setFocus();
}

