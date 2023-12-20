#include "Editions.h"

Editions::Editions(const QString& viewName, qModel* model) 
    : Entity(viewName, model)
{
    lbl_name = new QLabel;
    lbl_name->setText(tr("Name"));
    _layout->addWidget(lbl_name, 1);
    lineEdit_name = new QLineEdit;
    lineEdit_name->setMaxLength(64);
    connect(lineEdit_name, &QLineEdit::textChanged, this,  &Entity::lineEdit_isEmpty_checker);
    _layout->addWidget(lineEdit_name, 1);
    lbl_country = new QLabel;
    lbl_country->setText(tr("Country"));
    _layout->addWidget(lbl_country, 1);
    lineEdit_country = new QLineEdit;
    lineEdit_country->setMaxLength(64);
    _layout->addWidget(lineEdit_country, 1);
    for(int i = 0; i < _layout->count(); ++i)
    {
        _layout->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
    _layout->addStretch(6);
}

void Editions::setData(const Data& dataIn)
{
    _id = dataIn[Id].toInt();
    lineEdit_name->setText(dataIn[Edition::Name].toString());
    lineEdit_country->setText(dataIn[Edition::Country].toString());
}

const QStringList& Editions::getData()
{
    Entity::getData();
    _dataOut[Edition::Name] = lineEdit_name->text();
    if(lineEdit_country->text().isEmpty())
    {
        _dataOut[Edition::Country] = "NULL";
    }
    else
    {
        _dataOut[Edition::Country] = lineEdit_country->text();
    }
    return _dataOut;
}

void Editions::clear() 
{
    Entity::clear();
    lineEdit_name->clear();
    lineEdit_name->setStyleSheet("border-bottom: 1px solid grey;");
    lineEdit_country->clear();
}

bool Editions::isEmptyValues()
{
    if(lineEdit_name->text().isEmpty())
    {
        lineEdit_name->setStyleSheet("border-bottom: 1px solid red;");
        return true;
    }
    return false;
}
