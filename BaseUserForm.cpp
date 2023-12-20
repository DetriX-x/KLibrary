#include "BaseUserForm.h"
#include "ui_BaseUserForm.h"

BaseUserForm::BaseUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseUserForm)
{
    ui->setupUi(this);
    connect(ui->pushButton_exitProfile, &QPushButton::clicked,
            this, [this](){ emit this->exit(Exit); });
    leftSideAnim = new QPropertyAnimation(ui->leftSide, "maximumWidth");
    connect(leftSideAnim, &QPropertyAnimation::finished, this, &BaseUserForm::leftAnimFinished);
    connect(ui->pushButton_leftMenu, &QPushButton::clicked, this, &BaseUserForm::pushButtonForceAnim);
    model = new QSqlQueryModel(this);
    proxy = new QSortFilterProxyModel(model);
    proxy->setSourceModel(model);
    ui->tableView->setColumnHidden(0, true); // hide id
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(proxy);
    ui->tableView->setSortingEnabled(true);

    empty = new QWidget;
    QLabel* lbl_chooseRow = new QLabel;
    lbl_chooseRow->setText("Choose row");
    lbl_chooseRow->setAlignment(Qt::AlignCenter);
    QVBoxLayout* emptyLayout = new QVBoxLayout(empty);
    emptyLayout->addWidget(lbl_chooseRow);
    ui->rightSide->addWidget(empty);

    noInfo = new QWidget;
    QLabel* lbl_noInfo = new QLabel;
    lbl_noInfo->setText(tr("No Information"));
    lbl_noInfo->setAlignment(Qt::AlignCenter);
    QVBoxLayout* noInfoLayout = new QVBoxLayout(noInfo);
    noInfoLayout->addWidget(lbl_noInfo);
    ui->rightSide->addWidget(noInfo);
    ui->rightSide->setCurrentWidget(empty);

    skipWhiteSpace.setPattern("(,\\s+)|(\\s+)");
}

BaseUserForm::~BaseUserForm()
{
    delete ui;
}

void BaseUserForm::leftAnimFinished()
{

}

void BaseUserForm::pushButtonForceAnim()
{
    QPropertyAnimation* anim = leftSideAnim;
    QWidget* widget = ui->leftSide;
    int width = widget->width();
    int newWidth;
    if(width == Small)
    {
        widget->show();
    }
    if(width > Small)
    {
        newWidth = Small;
    }
    else
    {
        newWidth = Big; // optimal value of max width
    }
    anim->setDuration(300);
    anim->setStartValue(width);
    anim->setEndValue(newWidth);
    anim->setEasingCurve(QEasingCurve::InOutQuad);
    anim->start();
}

void BaseUserForm::clearSorting() const
{
    ui->tableView->horizontalHeader()->blockSignals(true);
    ui->tableView->horizontalHeader()->setSortIndicator(-1, Qt::DescendingOrder);
    ui->tableView->clearSelection();
    proxy->sort(-1);
    ui->tableView->horizontalHeader()->blockSignals(false);
}

void BaseUserForm::search(const QString& baseQuery)
{ // baseQuery should be like 'SELECT some FROM table'
    ui->rightSide->setCurrentWidget(empty);
    QString line = ui->lineEdit_search->text();
    QString filter;
    if(line.isEmpty())
    {
        model->setQuery(baseQuery);
        _filter = "";
        return;
    }
    QSqlQuery query;
    query.exec(baseQuery + " LIMIT 1");
    QSqlRecord record = query.record();
    QStringList attributes;
    for (int i = 0; i < record.count(); ++i)
    {
        attributes.push_back(record.fieldName(i));
    }
    QStringList words = line.split(skipWhiteSpace, Qt::SkipEmptyParts);
    for(int i = 0; i < attributes.size(); ++i)
    {
        for(int j = 0; j < words.size(); ++j)
        {
            filter += "lower(cast(" + attributes[i] +  " AS varchar)) LIKE lower(\'%" + words[j] + "%\') OR ";
        }
    }
    QString connector;
    if(baseQuery.contains("WHERE"))
    {
        connector = " AND (";
    }
    else
    {
        connector = " WHERE (";
    }
    _filter = " WHERE (" + filter.chopped(3) + ")";
    model->setQuery(baseQuery + connector + filter.chopped(3) + ")");
}


void BaseUserForm::reset() const
{
    ui->rightSide->setCurrentWidget(empty);
    this->clearSorting(); 
}


