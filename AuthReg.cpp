#include "AuthReg.h"
#include "BaseEnterForm.h"
#include "ui_AuthReg.h"

AuthReg::AuthReg(QWidget *parent, HashMap widgets) :
    QWidget(parent),
    ui(new Ui::AuthReg)
{
    ui->setupUi(this);
    ui->comboBox->hide();
    this->widgets = widgets;
    for(auto&[ind, widget] : this->widgets)
    {
        ui->widgetList->addWidget(widget);
    }
    ui->widgetList->setCurrentWidget(this->widgets[Page::Authorization]);
}

AuthReg::~AuthReg()
{
    delete ui;
}

void AuthReg::setWidget(QWidget *w) const
{
    ui->widgetList->setCurrentWidget(w);
}

void AuthReg::changeWidget(Page widget)
{
    auto form = qobject_cast<BaseEnterForm*>(ui->widgetList->currentWidget());
    if(form)
    {
        form->clearInputs();
    }
    try
    {
        ui->widgetList->setCurrentWidget(this->widgets.at(widget));
    }
    catch (const std::out_of_range& e)
    {
        qDebug() << QString(e.what());
    }
}
