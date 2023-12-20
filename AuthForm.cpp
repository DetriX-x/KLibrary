#include "AuthForm.h"
#include "qcheckbox.h"
#include "ui_BaseEnterForm.h"


AuthForm::AuthForm(QWidget *parent)
    : BaseEnterForm{parent}
{
    layout = new QHBoxLayout;
    checkBox = new QCheckBox(this);
    label = new QLabel(this);
    label->setText(tr("Remember Me"));
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(label, 1);
    layout->addWidget(checkBox, 1, Qt::AlignRight);
    layout->setSpacing(4);
    ui->baseLayout->insertLayout(8, layout, 1);
    ui->baseLayout->insertStretch(9, 1);
    connect(ui->pushButton_goTo, &QPushButton::clicked,
            this, [this](){ emit goTo(Page::Registration); });
    QWidget::setTabOrder(ui->lineEdit_password, checkBox);
}

RequestType AuthForm::request()
{
    const QString username = ui->lineEdit_username->text();
    const QString password = ui->lineEdit_password->text();
    QSqlQuery query;
    // check if username is a lib's name
    query.prepare("SELECT librarian_id, login, password "\
                  "FROM librarians WHERE login = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if(!query.exec())
    {
        return QueryError;
    }
    if(query.size() > 0) // admin found
    {
        return AuthorizationAdmin;
    }
    query.clear();
    // check if username is a reader's name
    query.prepare("SELECT reader_id, email, phone, login, password "\
                  "FROM readers WHERE login = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if(!query.exec())
    {
        return QueryError;
    }
    if(query.size() > 0)
    {
        // user has been successfuly signed up
        query.next();
        userId = query.value(0).toInt(); // set up current reader_id
        email = query.value(1).toString();
        phone = query.value(2).toString();
        return AuthorizationClient;
    }
    return AuthorizationFailed;
}

void AuthForm::clearInputs() const
{
    BaseEnterForm::clearInputs();
    checkBox->setChecked(false);
}
