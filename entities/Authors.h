#ifndef AUTHORS_H
#define AUTHORS_H

#include "Entity.h"

namespace Author{
    enum{
        Name = 1, Surname, Middlename
    };
}

class Authors : public Entity
{
public:
    Authors(const QString& viewName, qModel* model);

    virtual void setData(const Data& data) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

private:
    QLabel* lbl_name; 
    QLineEdit* lineEdit_name;
    QLabel* lbl_surname;
    QLineEdit* lineEdit_surname;
    QLabel* lbl_middleName;
    QLineEdit* lineEdit_middleName;
};

#endif // AUTHORS_H
