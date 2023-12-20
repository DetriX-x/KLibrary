#include "BaseEnterForm.h"
#include "ui_BaseEnterForm.h"

BaseEnterForm::BaseEnterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseEnterForm)
{
    ui->setupUi(this);
    checker = new InputChecker(this);
    connect(ui->lineEdit_username, &QLineEdit::textChanged,
            checker, &InputChecker::lineEditLoginChaneged);
    connect(ui->lineEdit_password, &QLineEdit::textChanged,
            checker, &InputChecker::lineEditPasswordChanged);
    connect(ui->pushButton_request, &QPushButton::clicked,
            this, &BaseEnterForm::pushButtonRequestClicked);
}

BaseEnterForm::~BaseEnterForm()
{
    delete ui;
}

bool BaseEnterForm::checkInput()
{
    bool isGoodLogin = checker->checkLineEdit(ui->lineEdit_username, InputType::Login);
    bool isGoodPassword = checker->checkLineEdit(ui->lineEdit_password, InputType::Password);
    const QString badLogin = tr("Invalid username. The nickname can only consist of letters of the Latin alphabet and numbers, must be at least 4 characters long and no more than 16, and the nickname cannot begin with a number");
    const QString badPassword = tr("Invalid password. The password can only consist of non-special characters of the Latin alphabet, must be at least 8 characters long and no more than 16, the password must contain at least 1 uppercase letter and at least one lowercase letter");
    if(!isGoodLogin && !isGoodPassword)
    {
        QMessageBox::warning(this, tr("Error"), badLogin + '\n' +badPassword);
        return false;
    }
    if(!isGoodLogin)
    {
        QMessageBox::warning(this, tr("Error"), badLogin);
        return false;
    }
    if(!isGoodPassword)
    {
        QMessageBox::warning(this, tr("Error"), badPassword);
        return false;
    }
    return true;
}

void BaseEnterForm::clearInputs() const
{
    ui->lineEdit_username->setFocus();
    ui->lineEdit_username->clear();
    ui->lineEdit_username->setStyleSheet("color: grey;");
    ui->lineEdit_password->clear();
    ui->lineEdit_password->setStyleSheet("color: grey;");
}

void BaseEnterForm::pushButtonRequestClicked()
{
    if(!checkInput())
    {
        return;
    }
    QString message;
    auto requestResult = this->request();
    switch (requestResult)
    {
    case RequestType::AuthorizationFailed:
        message = tr("Authorization failed. Invalid nickname or password");
        break;
    case RequestType::RegistrationFailed:
        message = tr("Registration failed. A user with the same name already exists");
        break;
    case RequestType::RegistrationDone:
        message = tr("Registration done successfully");
        emit goTo(Page::Authorization);
        break;
    case RequestType::QueryError:
        message = tr("Unknown error");
        break;
    default:
        emit requestDone(requestResult);
        return;
    }
    QMessageBox::information(this, tr("Information"), message);
}
