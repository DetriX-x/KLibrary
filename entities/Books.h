#ifndef BOOKS_H
#define BOOKS_H

#include "Entity.h"
#include "Relation.h"
#include <QComboBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QSet>

namespace BookTable{
    enum Table{
        Edition_id = 1, ISBN,
        Title, Lang, Year,
        Genre_Id, Quantity
    };
}

class Books : public Entity
{
public:
    Books(const QString& viewName, qModel* model, QSqlDatabase* db);

    virtual void setData(const Data& dataIn) override;

    virtual const QStringList& getData() override;

    virtual void clear() override;

    virtual bool isEmptyValues() override;

    virtual bool update() override;

    virtual int insert() override;

    virtual bool remove() override;

private slots:
    void on_cb_null_value(int);

    void on_pb_add_clicked();

private:

    bool isSameAuthors();

    const QString getInsertAuthorsQuery(int book_id);

    void initUi();

    void cleanScrollArea();

    QSqlDatabase* database;

    QComboBox* createComboBox();
    
    QLabel* lbl_title;
    QLineEdit* lineEdit_title;
    QLabel* lbl_genre;
    QComboBox* cb_genre;
    QLabel* lbl_lang;
    QLineEdit* lineEdit_lang;
    QLabel* lbl_year;
    QSpinBox* sp_year;
    QLabel* lbl_edition;
    QComboBox* cb_edition;
    QLabel* lbl_quantity;
    QSpinBox* sp_quantity;
    QLabel* lbl_isbn;
    QLineEdit* lineEdit_isbn;
    QLabel* lbl_authors;
    QScrollArea* scrollArea;
    QWidget* authorsComboboxes;
    QPushButton* pb_add;

    Relation* editionNameRelation;
    Relation* genreNameRelation;
    Relation* authorNameRelation;
};

#endif // BOOKS_H
