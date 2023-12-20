#ifndef AUTHFORM_H
#define AUTHFORM_H

#include "qcheckbox.h"
#include <BaseEnterForm.h>

class AuthForm : public BaseEnterForm
{
    Q_OBJECT
public:
    explicit AuthForm(QWidget *parent = nullptr);

    virtual RequestType request() override;

    virtual void clearInputs() const override;

    inline int getUserId() const { return userId;}

    inline const QString& getPhone() const { return this->phone; }

    inline const QString& getEmail() const { return this->email; }

    inline bool checked() const { return checkBox->checkState(); }

    inline void setChecked() { checkBox->setCheckState(Qt::Checked);}


signals:

private:
    QLabel* label;
    QCheckBox* checkBox;
    QHBoxLayout* layout;
    int userId;
    QString phone;
    QString email;
};

#endif // AUTHFORM_H
