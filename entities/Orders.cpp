#include "Orders.h"

Orders::Orders(const QString& viewName, qModel* model) :
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
    lbl_dateStart = new QLabel;
    lbl_dateStart->setText(tr("Date Start"));
    _layout->addWidget(lbl_dateStart, 1);
    dateStart = new QDateEdit;
    dateStart->setDisplayFormat(dateFormat);
    dateStart->setAlignment(Qt::AlignCenter);
    _layout->addWidget(dateStart, 1);
    lbl_dateEnd = new QLabel;
    lbl_dateEnd->setText(tr("Date End"));
    _layout->addWidget(lbl_dateEnd, 1);
    dateEnd = new QDateEdit;
    dateEnd->setDisplayFormat(dateFormat);
    dateEnd->setAlignment(Qt::AlignCenter);
    _layout->addWidget(dateEnd, 1);
    lbl_status = new QLabel;
    lbl_status->setText(tr("Status"));
    _layout->addWidget(lbl_status, 1);
    cb_status = new QComboBox;
    cb_status->addItem(tr("Inactive"));
    cb_status->addItem(tr("Active"));
    cb_status->addItem(tr("Not confirmed"));
    cb_status->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    _layout->addWidget(cb_status, 1);

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


void Orders::setData(const Data& dataIn)
{
    _id = dataIn[Id].toInt();

    readerLoginRelation->loadComboBox(cb_reader);
    int readerPKey = dataIn[OrderView::Reader_id].toInt(); 
    cb_reader->setCurrentIndex(readerLoginRelation->getIndexByPrimaryKey(readerPKey));

    bookTitleRelation->loadComboBox(cb_book);
    int bookPKey = dataIn[OrderView::Book_id].toInt();
    cb_book->setCurrentIndex(bookTitleRelation->getIndexByPrimaryKey(bookPKey));

    dateStart->setDate(dataIn[OrderView::DateStart].toDate());
    dateEnd->setDate(dataIn[OrderView::DateEnd].toDate());
    cb_status->setCurrentText(dataIn[OrderView::Status].toString());
}

const QStringList& Orders::getData()
{
     Entity::getData();
     _dataOut[OrderTable::Reader_id] =
         QString::number(readerLoginRelation->getPrimaryKeyByIndex(cb_reader->currentIndex())); 
     _dataOut[OrderTable::Book_id] =
            QString::number(bookTitleRelation->getPrimaryKeyByIndex(cb_book->currentIndex())); 
     _dataOut[OrderTable::DateStart] = dateStart->date().toString();
     _dataOut[OrderTable::DateEnd] = dateEnd->date().toString();
     _dataOut[OrderTable::Status] = cb_status->currentText();
     return _dataOut;
}

void Orders::clear()
{
     Entity::clear();
     bookTitleRelation->loadComboBox(cb_book);
     readerLoginRelation->loadComboBox(cb_reader);
     cb_reader->setCurrentIndex(0);
     cb_book->setCurrentIndex(0);
     dateStart->setDate(QDate::currentDate());
     dateEnd->setDate(QDate::currentDate().addDays(90));
     cb_status->setCurrentText("Active");
}

bool Orders::isEmptyValues()
{
     bool isBadVal = false;
     if(!cb_book->currentIndex())
         isBadVal = true;
     if(!cb_reader->currentIndex())
         isBadVal = true;
     return isBadVal;
}
