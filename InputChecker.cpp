#include "InputChecker.h"

InputChecker::InputChecker(QObject *parent) : QObject(parent)
{
    exprs.push_back(RegEx("^(?=.*[A-Za-z0-9]$)[A-Za-z][A-Za-z\\d.-]{3,16}$"));
    exprs.push_back(RegEx("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,16}$"));
    exprs.push_back(RegEx("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$"));
    exprs.push_back(RegEx("^[\\+]?[(]?[0-9]{3}[)]?[-\\s\\.]?[0-9]{3}[-\\s\\.]?[0-9]{4,6}$"));
}

void InputChecker::lineEditLoginChaneged(const QString &)
{
    auto lineEdit = qobject_cast<QLineEdit*>(QObject::sender());
    checkLineEdit(lineEdit, InputType::Login);
}

void InputChecker::lineEditPasswordChanged(const QString &)
{
    auto lineEdit = qobject_cast<QLineEdit*>(QObject::sender());
    checkLineEdit(lineEdit, InputType::Password);
}

void InputChecker::lineEditEmailChanged(const QString &)
{
    auto lineEdit = qobject_cast<QLineEdit*>(QObject::sender());
    checkLineEdit(lineEdit, InputType::Email);
}

void InputChecker::lineEditPhoneChanged(const QString &)
{
    auto lineEdit = qobject_cast<QLineEdit*>(QObject::sender());
    checkLineEdit(lineEdit, InputType::Phone);
}

bool InputChecker::checkLineEdit(QLineEdit* lineEdit, InputType type)
{
    auto& r = exprs[type];
    if(r.match(lineEdit->text()).hasMatch())
    {
        lineEdit->setStyleSheet("color: grey;");
        return true;
    }
    else
    {
        lineEdit->setStyleSheet("color: red;");
        return false;
    }
    return true;
}
