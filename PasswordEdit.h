#ifndef PASSWORDEDIT_H
#define PASSWORDEDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QIcon>
#include <QAction>
#include <QPixmap>

class PasswordEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit PasswordEdit(QWidget* parent = nullptr);

    QIcon* eyeVisible;
    QIcon* eyeInVisible;
    QAction* action;
public slots:
    void eyeClick(bool isVisible);
};

#endif // PASSWORDEDIT_H
