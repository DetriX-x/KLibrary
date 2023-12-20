#include "Readers.h"

Readers::Readers(const QString& viewName, qModel* model) 
    : Entity(viewName, model)
{
    lbl_login = new QLabel;
    lbl_login->setText(tr("Login"));
    _layout->addWidget(lbl_login, 1);
    lineEdit_login = new QLineEdit;
    lineEdit_login->setMaxLength(16);
    connect(lineEdit_login, &QLineEdit::textChanged, this, &Entity::lineEdit_isEmpty_checker);
    _layout->addWidget(lineEdit_login, 1);
    lbl_password = new QLabel;
    lbl_password->setText(tr("Password"));
    _layout->addWidget(lbl_password, 1);
    lineEdit_password = new QLineEdit;
    lineEdit_password->setMaxLength(16);
    connect(lineEdit_password, &QLineEdit::textChanged, this, &Entity::lineEdit_isEmpty_checker);
    _layout->addWidget(lineEdit_password, 1);
    lbl_phone = new QLabel;
    lbl_phone->setText(tr("Phone"));
    _layout->addWidget(lbl_phone, 1);
    lineEdit_phone = new QLineEdit;
    lineEdit_phone->setMaxLength(16);
    _layout->addWidget(lineEdit_phone, 1);
    lbl_email = new QLabel;
    lbl_email->setText(tr("Email"));
    _layout->addWidget(lbl_email, 1);
    lineEdit_email = new QLineEdit;
    lineEdit_email->setMaxLength(256);
    _layout->addWidget(lineEdit_email, 1);
    for(int i = 0; i < _layout->count(); ++i)
    {
        _layout->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
    _layout->addStretch(6);
}

void Readers::setData(const Data& dataIn)
{
    _id = dataIn[Id].toInt();
    lineEdit_login->setText(dataIn[Reader::Login].toString());
    lineEdit_password->setText(dataIn[Reader::Password].toString());
    lineEdit_phone->setText(dataIn[Reader::Phone].toString());
    lineEdit_email->setText(dataIn[Reader::Email].toString());
}

const QStringList& Readers::getData()
{
    Entity::getData();
    _dataOut[Reader::Login] = lineEdit_login->text();
    _dataOut[Reader::Password] = lineEdit_password->text();
    if(lineEdit_phone->text().isEmpty())
    {
        _dataOut[Reader::Phone] = "NULL";
    }
    else
    {
        _dataOut[Reader::Phone] = lineEdit_phone->text();
    }
    if(lineEdit_email->text().isEmpty())
    {
        _dataOut[Reader::Email] = "NULL";
    }
    else
    {
        _dataOut[Reader::Email] = lineEdit_email->text();
    }
    return _dataOut;
}

void Readers::clear() 
{
    Entity::clear();
    lineEdit_login->clear();
    lineEdit_login->setStyleSheet("border-bottom: 1px solid grey;");
    lineEdit_password->clear();
    lineEdit_password->setStyleSheet("border-bottom: 1px solid grey;");
    lineEdit_phone->clear();
    lineEdit_email->clear();
}

bool Readers::isEmptyValues()
{
    bool isBadVal = false;
    if(lineEdit_login->text().isEmpty())
    {
        lineEdit_login->setStyleSheet("border-bottom: 1px solid red;");
        isBadVal = true;
    }
    if(lineEdit_password->text().isEmpty())
    {
        lineEdit_login->setStyleSheet("border-bottom: 1px solid red;");
        isBadVal = true;
    }
    return isBadVal;
}
