#include "PasswordEdit.h"

PasswordEdit::PasswordEdit(QWidget *parent) : QLineEdit(parent)
{
    this->setEchoMode(QLineEdit::Password);
    QPixmap p(":/imgs/visible-96.png");
    eyeVisible = new QIcon(p);
    eyeInVisible = new QIcon(":/imgs/invisible-96.png");
    action = new QAction(*eyeVisible, "", this);
    action->setCheckable(true);
    connect(action, &QAction::toggled, this, &PasswordEdit::eyeClick);
    this->addAction(action, QLineEdit::TrailingPosition);
}

void PasswordEdit::eyeClick(bool isVisible)
{
    if(isVisible)
    {
        action->setIcon(*eyeInVisible);
        this->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        action->setIcon(*eyeVisible);
        this->setEchoMode(QLineEdit::Password);
    }
}
