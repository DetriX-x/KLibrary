#ifndef EDITIONS_H
#define EDITIONS_H

#include "Entity.h"
namespace Edition
{
    enum{
        Name = 1, Country
    };
}

class Editions : public Entity
{
public:
    Editions(const QString& viewName, qModel* model);

    virtual void setData(const Data& data) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

private:
    QLabel* lbl_name;
    QLabel* lbl_country;
    QLineEdit* lineEdit_name;
    QLineEdit* lineEdit_country;
};

#endif // EDITIONS_H
