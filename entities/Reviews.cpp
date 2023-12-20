#include "Reviews.h"

Reviews::Reviews(const QString& viewName, qModel* model) :
    Entity(viewName, model)
{
    lbl_reader = new QLabel;
    lbl_reader->setText(tr("Reader"));
    _layout->addWidget(lbl_reader, 1);
    cb_reader = new QComboBox;
    cb_reader->addItem("NULL");
    cb_reader->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    _layout->addWidget(cb_reader, 1);
    lbl_book = new QLabel;
    lbl_book->setText(tr("Book"));
    _layout->addWidget(lbl_book, 1);
    cb_book = new QComboBox;
    cb_book->addItem("NULL");
    cb_book->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    _layout->addWidget(cb_book, 1);
    lbl_rating = new QLabel;
    lbl_rating->setText(tr("Rating"));
    _layout->addWidget(lbl_rating, 1);
    sb_rating = new QSpinBox;
    sb_rating->setMinimum(1);
    sb_rating->setMaximum(5);
    sb_rating->setAlignment(Qt::AlignCenter);
    _layout->addWidget(sb_rating, 1);
    lbl_content = new QLabel;
    lbl_content->setText(tr("Content"));
    _layout->addWidget(lbl_content, 1);
    lineEdit_content = new QLineEdit;
    _layout->addWidget(lineEdit_content, 1);
    lbl_dateTime = new QLabel;
    lbl_dateTime->setText(tr("Date"));
    _layout->addWidget(lbl_dateTime, 1);
    dateTimeEdit = new QDateTimeEdit;
    dateTimeEdit->setDisplayFormat(dateTimeFormat);
    dateTimeEdit->setAlignment(Qt::AlignCenter);
    _layout->addWidget(dateTimeEdit, 1);

    for(int i = 0; i < _layout->count(); ++i)
    {
        _layout->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
    _layout->addStretch(3);

    this->readerLoginRelation = new Relation("reader_id", "login", "readers");
    this->bookTitleRelation = new Relation("book_id", "title", "books");
    cb_reader->addItems(readerLoginRelation->getRelationValues());
    cb_book->addItems(bookTitleRelation->getRelationValues());
}

void Reviews::setData(const Data& dataIn)
{
    _id = dataIn[Id].toInt();

    readerLoginRelation->loadComboBox(cb_reader);
    int readerPKey = dataIn[ReviewView::Reader_id].toInt(); 
    cb_reader->setCurrentIndex(readerLoginRelation->getIndexByPrimaryKey(readerPKey));

    bookTitleRelation->loadComboBox(cb_book);
    int bookPKey = dataIn[ReviewView::Book_id].toInt();
    cb_book->setCurrentIndex(bookTitleRelation->getIndexByPrimaryKey(bookPKey));

    sb_rating->setValue(dataIn[ReviewView::Rating].toInt());
    lineEdit_content->setText(dataIn[ReviewView::Content].toString());
    dateTimeEdit->setDateTime(dataIn[ReviewView::DateTime].toDateTime());
}

const QStringList& Reviews::getData() 
{
     Entity::getData();
     if(!cb_reader->currentIndex())
     {
         _dataOut[ReviewTable::Reader_id] = "NULL";
     }
     else
     {
        _dataOut[ReviewTable::Reader_id] =
            QString::number(readerLoginRelation->getPrimaryKeyByIndex(cb_reader->currentIndex())); 
     }
     _dataOut[ReviewTable::Book_id] =
            QString::number(bookTitleRelation->getPrimaryKeyByIndex(cb_book->currentIndex())); 
     _dataOut[ReviewTable::Rating] = QString::number(sb_rating->value());
     _dataOut[ReviewTable::Content] = lineEdit_content->text();
     _dataOut[ReviewTable::DateTime] = dateTimeEdit->dateTime().toString();
     return _dataOut;
}
                              
void Reviews::clear() 
{
     Entity::clear();
     bookTitleRelation->loadComboBox(cb_book);
     readerLoginRelation->loadComboBox(cb_reader);
     cb_reader->setCurrentIndex(0);
     cb_book->setCurrentIndex(0);
     sb_rating->setValue(1);
     lineEdit_content->clear();
     dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}
                              
bool Reviews::isEmptyValues() 
{
     bool isBadVal = false;
     if(!cb_book->currentIndex())
         isBadVal = true;
     return isBadVal;
}
