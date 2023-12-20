#ifndef INPUTCHECKER_H
#define INPUTCHECKER_H

#include <QObject>
#include <QRegularExpression>
#include <QLineEdit>

enum InputType{
    Login, Password, Email, Phone
};

typedef QRegularExpression RegEx;

class InputChecker : public QObject
{
    Q_OBJECT
public:
    InputChecker(QObject* parent = nullptr);

    bool checkLineEdit(QLineEdit *lineEdit, InputType type);

public slots:
    void lineEditPasswordChanged(const QString&);

    void lineEditLoginChaneged(const QString&);

    void lineEditEmailChanged(const QString&);

    void lineEditPhoneChanged(const QString&);

private:
    QVector<RegEx> exprs;
};

#endif // INPUTCHECKER_H
