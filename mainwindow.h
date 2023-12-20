#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>

#include "RegisterForm.h"
#include "AuthReg.h"
#include "AuthForm.h"
#include "ClientForm.h"
#include "AdminForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool writeDataToFile() const;

    bool readDataFromFile() const;

public slots:
    void changePage(RequestType requestResult);

private:
    Ui::MainWindow *ui;
    AuthForm* authUI;
    RegisterForm* regUI;
    AuthReg* authReg;
    ClientForm* clientUI;
    AdminForm* adminUI;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
