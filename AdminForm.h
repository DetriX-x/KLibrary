#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QButtonGroup>

#include "BaseUserForm.h"
#include "./entities/Entity.h"
#include "./entities/Editions.h"
#include "./entities/Readers.h"
#include "./entities/Authors.h"
#include "./entities/Genres.h"
#include "./entities/Reviews.h"
#include "./entities/Orders.h"
#include "./entities/Relation.h"
#include "./entities/Books.h"
#include "array"

enum tables{
    books, authors, readers,
    reviews, orders, genres,
    editions
};

class AdminForm : public BaseUserForm
{
    Q_OBJECT
public:
    explicit AdminForm(QWidget *parent = nullptr, QSqlDatabase* db = nullptr);

    void pb_fromLeftSide_toggled(bool isChecked);

    virtual void reset() const override;

protected slots:
    virtual void leftAnimFinished() override {}

    virtual void on_tableView_clicked(const QModelIndex &index) override;

    virtual void on_lineEdit_search_returnPressed() override; 

    void pb_ok_clicked();

    void pb_addRow_clicked();

    void pb_removeRow_clicked();

private:
    void initUi();

    void initEntities();

private:
    QSqlDatabase* _db;
    QVBoxLayout* leftSideLayout;
    std::array<Entity*, 7> entities;
    QButtonGroup buttonGroup;
    QPushButton* pb_removeRow;
    QPushButton* pb_addRow;
    QPushButton* pb_books;
    QString rowId;
    QWidget* rowInfo;
    QStackedWidget* rightSideRow; 
    QPushButton* pb_ok;
};

#endif // ADMINFORM_H
