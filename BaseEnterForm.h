#ifndef BASEENTERFORM_H
#define BASEENTERFORM_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>

#include "InputChecker.h"
#include "Consts.h"
#include "ui_BaseEnterForm.h"

enum Position{
    AfterPassword = 7
};

namespace Ui {
class BaseEnterForm;
}

class BaseEnterForm : public QWidget
{
    Q_OBJECT

public:
    explicit BaseEnterForm(QWidget *parent = nullptr);
    virtual ~BaseEnterForm();

    virtual bool checkInput();

    virtual void clearInputs() const;

    inline const QString getUserName() const { return ui->lineEdit_username->text(); }

    inline const QString getUserPassword() const { return ui->lineEdit_password->text(); }

    inline void setUserName(const QString& s) const { ui->lineEdit_username->setText(s); }

    inline void setUserPassword(const QString& s) const { ui->lineEdit_password->setText(s); }

public slots:
    void pushButtonRequestClicked();

signals:
    void goTo(Page);

    void requestDone(RequestType);

protected:
    virtual RequestType request() = 0;

    InputChecker* checker;
    Ui::BaseEnterForm *ui;
};

#endif // BASEENTERFORM_H
