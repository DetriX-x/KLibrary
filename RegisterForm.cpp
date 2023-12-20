#include "RegisterForm.h"
#include "qpushbutton.h"
#include "ui_BaseEnterForm.h"

RegisterForm::RegisterForm(QWidget *parent)
    : BaseEnterForm{parent}
{
    ui->label_main->setText(tr("REGISTRATION"));
    ui->pushButton_goTo->setText(tr("Back"));
    ui->pushButton_request->setText(tr("Register"));
    ui->label_img->setPixmap(QPixmap(":/imgs/person-add-96"));
    layout = new QVBoxLayout;
    verification = new PasswordEdit(this);
    verification->setPlaceholderText(tr("Verify password..."));
    verification->setAlignment(Qt::AlignBottom);
    verification->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(verification, &QLineEdit::textChanged,
            checker, &InputChecker::lineEditPasswordChanged);
    label = new QLabel(this);
    label->setText(tr("Verification"));
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(label, 1);
    layout->addWidget(verification, 1);
    layout->setSpacing(4);
    ui->baseLayout->insertLayout(8, layout, 1);
    ui->baseLayout->insertStretch(9, 1);
    connect(ui->pushButton_goTo, &QPushButton::clicked,
            this, [this](){ emit goTo(Page::Authorization); });
    QWidget::setTabOrder(ui->lineEdit_password, verification);
}

RequestType RegisterForm::request()
{
    const QString username = ui->lineEdit_username->text();
    const QString password = ui->lineEdit_password->text();
    // checking user input in database...
    QSqlQuery query;
    query.prepare("SELECT reader_id, login FROM readers WHERE login = :username");
    query.bindValue(":username", username);
    if(!query.exec())
    {
        return QueryError;
    }
    if(query.size() != 0)
    { // account with login - 'username' exists in database
        return RegistrationFailed;
    }
    // register new user
    query.clear();
    query.prepare("INSERT INTO readers (login, password) VALUES (:username, :password);");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if(!query.exec())
    {
        return QueryError;
    }
    this->clearInputs();
    ui->pushButton_goTo->setFocus();
    // user has been successfuly registered
    return RequestType::RegistrationDone;
}

bool RegisterForm::checkInput()
{
    bool isMisMatch = false;
    if(ui->lineEdit_password->text() != verification->text()
        or verification->text().isEmpty())
    {
        isMisMatch = true;
        ui->lineEdit_password->setStyleSheet("color: red");
        verification->setStyleSheet("color: red");
    }
    if(!BaseEnterForm::checkInput())
    {
        return false;
    }
    if(isMisMatch)
    {
        QMessageBox::warning(this, "Error", "Password mismatch");
        return false;
    }
    return true;
}

void RegisterForm::clearInputs() const
{
    BaseEnterForm::clearInputs();
    verification->clear();
    verification->setStyleSheet("color: grey;");
}
