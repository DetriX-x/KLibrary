#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("KLibrary");

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("library_db_2");
    db.setUserName("ketrix");
    db.setPassword("AW_igniTE_01");
    if(!db.open())
    {
        qDebug() << tr("Error! Can't connect to database...");
        QMessageBox::critical(this, tr("Critical"), db.lastError().text());
        db.close();
        exit(1);
    }


    authUI = new AuthForm(this);
    regUI = new RegisterForm(this);
    authReg = new AuthReg(this, HashMap{{Page::Authorization, authUI},
                                        {Page::Registration, regUI}});
    clientUI = new ClientForm(this);
    adminUI = new AdminForm(this, &db);
    connect(authUI, &AuthForm::goTo, authReg, &AuthReg::changeWidget);
    connect(regUI, &RegisterForm::goTo, authReg, &AuthReg::changeWidget);
    connect(authUI, &BaseEnterForm::requestDone, this, &MainWindow::changePage);
    connect(regUI, &BaseEnterForm::requestDone, this, &MainWindow::changePage);
    connect(clientUI, &BaseUserForm::exit, this, &MainWindow::changePage);
    connect(adminUI, &BaseUserForm::exit, this, &MainWindow::changePage);
    ui->stackedWidget->addWidget(authReg);
    ui->stackedWidget->setCurrentWidget(authReg);
    ui->stackedWidget->addWidget(clientUI);
    ui->stackedWidget->addWidget(adminUI);
    readDataFromFile();
}

MainWindow::~MainWindow()
{
    writeDataToFile();
    delete ui;
}

bool MainWindow::writeDataToFile() const
{
    QFile file("data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream out(&file);
    if(!authUI->checked())
    {
        out << "Unremembered\n";
        file.close();
        return false;
    }
    out << "Remembered\n";
    out << authUI->getUserName() << '\n';
    out << authUI->getUserPassword() << '\n';
    out.flush();
    file.close();
    return true;
}

bool MainWindow::readDataFromFile() const
{
    QString dataFileName{"data.txt"};
    if(!QFile::exists(dataFileName))
    {
        return false;
    }
    QFile file(dataFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream in(&file);
    QString s;
    in >> s;
    if(s != "Remembered")
    {
        return false;
    }
    authUI->setChecked();
    in >> s;
    authUI->setUserName(s);
    in >> s;
    authUI->setUserPassword(s);
    authUI->pushButtonRequestClicked();
    file.close();
    return true;

}

void MainWindow::changePage(RequestType requestResult)
{
    if(requestResult == RequestType::AuthorizationClient)
    {
        clientUI->setUserName(authUI->getUserName());
        clientUI->setUserId(authUI->getUserId());
        clientUI->setUserPhone(authUI->getPhone());
        clientUI->setUserEmail(authUI->getEmail());
        clientUI->reset();
        ui->stackedWidget->setCurrentWidget(clientUI);
    }
    else if(requestResult == RequestType::AuthorizationAdmin)
    {
        adminUI->clearSorting();
        adminUI->setUserName(authUI->getUserName());
        adminUI->reset();
        ui->stackedWidget->setCurrentWidget(adminUI);
    }
    else if(requestResult == RequestType::Exit)
    {
        authUI->clearInputs();
        ui->stackedWidget->setCurrentWidget(authReg);
    }
}

