#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include "BaseEnterForm.h"
#include "PasswordEdit.h"

class RegisterForm : public BaseEnterForm
{
    Q_OBJECT
public:
    explicit RegisterForm(QWidget *parent = nullptr);

    virtual RequestType request() override;

    virtual bool checkInput() override;

    virtual void clearInputs() const override;

signals:

private:
    QVBoxLayout* layout;
    PasswordEdit* verification;
    QLabel* label;

};

#endif // REGISTERFORM_H
