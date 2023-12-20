#ifndef ORDERS_H
#define ORDERS_H

#include "Entity.h"
#include "Relation.h"


namespace OrderView{
    enum ViewData{
        Reader_id = 1, Book_id = 3,
        DateStart = 5, DateEnd = 6, Status = 7
    };
}

namespace OrderTable{
    enum Table{
        Reader_id = 1, Book_id,
        DateStart, DateEnd, Status
    };
}

class Orders : public Entity
{
public:
    Orders(const QString& viewName, qModel* model);

    virtual void setData(const Data& dataIn) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

private:
    QLabel* lbl_reader;
    QComboBox* cb_reader;
    QLabel* lbl_book;
    QComboBox* cb_book;
    QLabel* lbl_dateStart;
    QDateEdit* dateStart;
    QLabel* lbl_dateEnd;
    QDateEdit* dateEnd;
    QLabel* lbl_status;
    QComboBox* cb_status;

    Relation* readerLoginRelation;
    Relation* bookTitleRelation;
};

#endif // ORDERS_H
