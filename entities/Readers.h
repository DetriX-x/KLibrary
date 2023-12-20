#ifndef READERS_H
#define READERS_H

#include "Entity.h"

namespace Reader{
    enum {
        Login = 1, Password, Phone, Email
    };
}


class Readers : public Entity
{
public:
    Readers(const QString& viewName, qModel* model);

    virtual void setData(const Data& data) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

private:
    QLabel* lbl_login; 
    QLineEdit* lineEdit_login;
    QLabel* lbl_password;
    QLineEdit* lineEdit_password;
    QLabel* lbl_phone;
    QLineEdit* lineEdit_phone;
    QLabel* lbl_email;
    QLineEdit* lineEdit_email;
};

#endif // READERS_H
