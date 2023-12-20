#ifndef BASEUSERFORM_H
#define BASEUSERFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QString>

#include "Consts.h"
#include "ui_BaseUserForm.h"

enum Width{
    Small = 86, Big = 500
};

const int ICON_SIZE = 54;

namespace Ui {
class BaseUserForm;
}

class BaseUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit BaseUserForm(QWidget *parent = nullptr);
    virtual ~BaseUserForm();

    inline void setUserName(const QString name) { ui->label_username->setText(name); }

    inline void setUserId(int userId) { this->userId = userId; }

    virtual void reset() const;

    void clearSorting() const;

    void search(const QString& baseQuery);

signals:
    void exit(RequestType);

protected slots:
    virtual void leftAnimFinished() = 0;

    virtual void on_tableView_clicked(const QModelIndex &index) = 0;

    virtual void on_lineEdit_search_returnPressed() = 0;

    void pushButtonForceAnim();

protected:
    Ui::BaseUserForm *ui;
    int userId;
    QPropertyAnimation* leftSideAnim;
    QSqlQueryModel* model;
    QSortFilterProxyModel* proxy;
    QWidget* empty;
    QWidget* noInfo;
    QRegularExpression skipWhiteSpace;
    QString _filter;
};

#endif // BASEUSERFORM_H
