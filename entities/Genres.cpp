#include "Genres.h"

Genres::Genres(const QString& viewName, qModel* model) :
    Entity(viewName, model)
{
    lbl_name = new QLabel;
    lbl_name->setText(tr("Name"));
    _layout->addWidget(lbl_name, 1);
    lineEdit_name = new QLineEdit;
    lineEdit_name->setMaxLength(32);
    _layout->addWidget(lineEdit_name, 1);
    connect(lineEdit_name, &QLineEdit::textChanged, this, &Entity::lineEdit_isEmpty_checker);
    for(int i = 0; i < _layout->count(); ++i)
    {
        _layout->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
    _layout->addStretch(10);
}

void Genres::setData(const Data& dataIn)
{
    _id = dataIn[Id].toInt();
    lineEdit_name->setText(dataIn[Genre::Name].toString());
}
                               
const QStringList& Genres::getData() 
{
    Entity::getData();
    _dataOut[Genre::Name] = lineEdit_name->text();
    return _dataOut;
}
                              
void Genres::clear() 
{
    Entity::clear();
    lineEdit_name->clear();
    lineEdit_name->setStyleSheet("border-bottom: 1px solid grey;");
}
                              
bool Genres::isEmptyValues() 
{
    bool isBadVal = false;
    if(lineEdit_name->text().isEmpty())
    {
        lineEdit_name->setStyleSheet("border-bottom: 1px solid red;");
        isBadVal = true;
    }
    return isBadVal;
}
