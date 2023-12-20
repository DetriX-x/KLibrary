#include "Authors.h"

Authors::Authors(const QString& viewName, qModel* model) :
    Entity(viewName, model)
{
    lbl_name = new QLabel;
    lbl_name->setText(tr("Name"));
    _layout->addWidget(lbl_name, 1);
    lineEdit_name = new QLineEdit;
    lineEdit_name->setMaxLength(64);
    _layout->addWidget(lineEdit_name, 1);
    connect(lineEdit_name, &QLineEdit::textChanged, this, &Entity::lineEdit_isEmpty_checker);
    lbl_surname = new QLabel;
    lbl_surname->setText(tr("Surname"));
    _layout->addWidget(lbl_surname, 1);
    lineEdit_surname = new QLineEdit;
    lineEdit_surname->setMaxLength(64);
    connect(lineEdit_surname, &QLineEdit::textChanged, this, &Entity::lineEdit_isEmpty_checker);
    _layout->addWidget(lineEdit_surname, 1);
    lbl_middleName = new QLabel;
    lbl_middleName->setText(tr("Middlename"));
    _layout->addWidget(lbl_middleName, 1);
    lineEdit_middleName = new QLineEdit;
    lineEdit_middleName->setMaxLength(64);
    _layout->addWidget(lineEdit_middleName, 1);
    for(int i = 0; i < _layout->count(); ++i)
    {
        _layout->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
    _layout->addStretch(6);
}

void Authors::setData(const Data& dataIn)
{
    _id = dataIn[Id].toInt();
    lineEdit_name->setText(dataIn[Author::Name].toString());
    lineEdit_surname->setText(dataIn[Author::Surname].toString());
    lineEdit_middleName->setText(dataIn[Author::Middlename].toString());
}
                                         
const QStringList& Authors::getData()
{
    Entity::getData();
    _dataOut[Author::Name] = lineEdit_name->text();
    _dataOut[Author::Surname] = lineEdit_surname->text();
    if(lineEdit_middleName->text().isEmpty())
    {
        _dataOut[Author::Middlename] = "NULL";
    }
    else
    {
        _dataOut[Author::Middlename] = lineEdit_middleName->text();
    }
    return _dataOut;
}
                                         
void Authors::clear()
{
    Entity::clear();
    lineEdit_name->clear();
    lineEdit_name->setStyleSheet("border-bottom: 1px solid grey;");
    lineEdit_surname->clear();
    lineEdit_surname->setStyleSheet("border-bottom: 1px solid grey;");
    lineEdit_middleName->clear();
}
                                         
bool Authors::isEmptyValues() 
{
    bool isBadVal = false;
    if(lineEdit_name->text().isEmpty())
    {
        lineEdit_name->setStyleSheet("border-bottom: 1px solid red;");
        isBadVal = true;
    }
    if(lineEdit_surname->text().isEmpty())
    {
        lineEdit_surname->setStyleSheet("border-bottom: 1px solid red;");
        isBadVal = true;
    }
    return isBadVal;
}
