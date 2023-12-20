#ifndef ENTITY_H
#define ENTITY_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQueryModel>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTimeEdit>


typedef QSqlQueryModel qModel;

typedef QVector<QVariant> Data;

const int Id = 0;

class Entity : public QObject
{
    Q_OBJECT

public:
    explicit Entity(const QString& viewName, qModel* model);
    virtual ~Entity() {}

    virtual void setData(const Data& dataIn) = 0;

    virtual const QStringList& getData();

    virtual void clear();

    virtual bool update();

    virtual int insert();

    virtual bool remove();

    virtual bool isEmptyValues() = 0;

    void select(QString whereFilter = "") const;

    void setUserFriendlyFieldNames(const QStringList& list);

    void setTableName(const QString& tableName); 

    inline QWidget* form() { return _form; }

    inline int getId() const { return _id; }

    inline const QStringList& getFieldNames() const { return _fieldNames; }

    inline const QString& getQuery() const { return _query; }

    void addDataToQueryContent(const QString& data, QString& queryContent) const;

public slots:
    void lineEdit_isEmpty_checker(const QString& s);


protected:
    int _id = 0;
    QString _query;
    QString _viewName;
    QString _tableName;
    qModel* _model;
    QStringList _fieldNames;
    QStringList _userFrendlyFieldNames;
    QStringList _dataOut;
    QWidget* _form = nullptr;
    const char* dateFormat = "yyyy-MM-dd";
    const char* dateTimeFormat = "yyyy-MM-dd hh:mm:ss";
    QVBoxLayout* _layout; 
};

#endif // ENTITY_H
