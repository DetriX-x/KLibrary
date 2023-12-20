#ifndef REVIEWS_H
#define REVIEWS_H

#include "Entity.h"
#include "Relation.h"

namespace ReviewView{
    enum ViewData{
        Reader_id = 1, Book_id = 3,
        Rating = 5, Content, DateTime = 7
    };
}

namespace ReviewTable{
    enum Table{
        Reader_id = 1, Book_id,
        Rating, Content, DateTime
    };
}

class Reviews : public Entity
{
public:
    Reviews(const QString& viewName, qModel* model);

    virtual void setData(const Data& dataIn) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

private:
    QLabel* lbl_reader;
    QComboBox* cb_reader;
    QLabel* lbl_book;
    QComboBox* cb_book;
    QLabel* lbl_rating;
    QSpinBox* sb_rating; 
    QLabel* lbl_content;
    QLineEdit* lineEdit_content;
    QLabel* lbl_dateTime;
    QDateTimeEdit* dateTimeEdit;
    Relation* readerLoginRelation;
    Relation* bookTitleRelation;
};

#endif // REVIEWS_H
