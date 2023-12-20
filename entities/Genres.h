#ifndef GENRES_H
#define GENRES_H

#include "Entity.h"

namespace Genre{
    enum{
        Name = 1
    };
}

class Genres : public Entity
{
public:
    Genres(const QString& viewName, qModel* model);

    virtual void setData(const Data& data) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

private:
    QLabel* lbl_name; 
    QLineEdit* lineEdit_name;
};

#endif // GENRES_H
