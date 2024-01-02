#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include "BaseUserForm.h"
#include "InputChecker.h"

#include <QProgressBar>
#include <QTextEdit>
#include <QSpinBox>
#include <QDateTime>

#include <utility>

namespace reviews_res
{
    enum
    {
        reader_id = 1, book_id = 3, login = 2,
        rating = 5, content = 6, datetime = 7
    };
}

namespace order_res{
    enum
    {
        order_id = 0, book_id = 1, status = 2 
    };
}

const int MAX_REVIEW_LEN = 80;

class ClientForm : public BaseUserForm
{
    Q_OBJECT
public:
    explicit ClientForm(QWidget *parent = nullptr);

    virtual void reset() const override;

    void setUserPhone(const QString phone) { le_phone->setText(phone); }

    inline void setUserEmail(const QString email) { le_email->setText(email); }

    void setViewHeaders(bool isAllBooksMode) const;

    void selectBookInfo(const QString& bookId);

    void saveReview(int bookId, const QString& text, double rating);

private:
    void clearBookInfo() const;

    bool hasActiveOrder(int bookId, int userId);

    std::pair<QStringList, int> parseReviews(QSqlQuery& query) const;

protected slots:
    virtual void leftAnimFinished() override;

    virtual void on_tableView_clicked(const QModelIndex& index) override;

    virtual void on_lineEdit_search_returnPressed() override;

    void saveUserInfo();

    void pb_myBooks_clicked();

    void myReview_textChanged();

    void pb_takeBook_clicked();

    void pb_cancelOrder_clicked();

private:
    QLineEdit* le_email;
    QLineEdit* le_phone;
    QPushButton* pb_saveUserInfo;
    QPushButton* pb_myBooks;
    QLabel* lbl_email;
    QLabel* lbl_phone;
    InputChecker* checker;
    bool isAllBooksMode = true;
    QString bookId;
    QString orderId;

    // right side widgets
    // bookInfo
    QWidget* book;
    QLabel* lbl_rating;
    QProgressBar* bar;
    QLabel* lbl_reviews;
    QTextEdit* reviews;
    QLabel* lbl_myReview;
    QTextEdit* myReview;
    QLabel* lbl_myGrade;
    QSpinBox* myGrade;
    QPushButton* pb_saveReview;
    QPushButton* pb_takeBook;
    // orderInfo
    QWidget* orderInfo;
    QPushButton* pb_cancelOrder;
};

#endif // CLIENTFORM_H
