#ifndef AUTHREG_H
#define AUTHREG_H

#include <QWidget>
#include <unordered_map>

#include <Consts.h>

typedef std::unordered_map<int, QWidget*> HashMap;

namespace Ui {
class AuthReg;
}

class AuthReg : public QWidget
{
    Q_OBJECT

public:
    explicit AuthReg(QWidget *parent = nullptr,
                     HashMap widgets = HashMap());
    ~AuthReg();

    void setWidget(QWidget *w) const;

public slots:
    void changeWidget(Page widget);

private:
    Ui::AuthReg *ui;
    HashMap widgets;
};

#endif // AUTHREG_H
