#include "Entity.h"

Entity::Entity(const QString& viewName, qModel* model)
    : _viewName(viewName), _model(model)
{
    _form = new QWidget;
    _layout = new QVBoxLayout;
    _form->setLayout(_layout);
    _query = "SELECT * FROM " + _viewName;
}

void Entity::setTableName(const QString& tableName) 
{
    this->_tableName = tableName;
    QSqlQuery q;
    if(!q.exec("SELECT * FROM " + _tableName + " WHERE false")) 
    {
        qDebug() << "error: can not execute query: " << _tableName;
    }
    auto record = q.record();
    for(int i = 0; i < record.count(); ++i)
    {
        _fieldNames.push_back(record.fieldName(i));
    }
    _dataOut.resize(_fieldNames.size());
}

void Entity::select(QString whereFilter) const
{
    _model->setQuery(std::move(_query) + whereFilter);
    int i = 0;
    for(auto field : _userFrendlyFieldNames)
    {
        _model->setHeaderData(i++, Qt::Horizontal, field);
    }
}

void Entity::setUserFriendlyFieldNames(const QStringList& list)
{
    for(auto& field : list)
    {
        _userFrendlyFieldNames.push_back(field);
    } 
}

bool Entity::update()
{
    if(isEmptyValues())
    {
        return false;
    }
    auto data = getData();
    QSqlQuery q;
    QString queryContent("UPDATE " + _tableName + " SET ");
    for(int i = 1; i < _fieldNames.size(); ++i)
    {
        queryContent += (_fieldNames[i] + " = ");
        addDataToQueryContent(data[i], queryContent);
    }
    queryContent = queryContent.chopped(2);
    queryContent += " WHERE " + _fieldNames[0] + " = " + QString::number(_id);
    qDebug() << queryContent;
    if(!q.exec(queryContent))
        return false;
    return true;
}

int Entity::insert()
{
    if(isEmptyValues())
    {
        return false;
    }
    auto data = getData();
    QSqlQuery q;
    QString queryContent("INSERT INTO " + _tableName + '(');
    for(int i = 1; i < _fieldNames.size(); ++i)
    {
        queryContent += (_fieldNames[i] + ", "); 
    }
    queryContent = queryContent.chopped(2);
    queryContent += ") VALUES(";
    for(int i = 1; i < _fieldNames.size(); ++i)
    {
        addDataToQueryContent(data[i], queryContent);
    }
    queryContent = queryContent.chopped(2);
    queryContent += ')';
    qDebug() << queryContent;
    if(!q.exec(queryContent))
        return false;
    return q.lastInsertId().toInt();
}

void Entity::addDataToQueryContent(const QString& data, QString& content) const
{
    if(data == "NULL")
    {
        content += (data + ", ");
    }
    else
    {
        content += ("\'" + data + "\', "); 
    }
}

bool Entity::remove()
{
    auto data = getData();
    if(data[0] == "0")
    {
        return false;
    }
    QSqlQuery q;
    QString queryContent("DELETE FROM " + _tableName + " WHERE ");
    queryContent += _fieldNames[0] + " = " + data[0];
    qDebug() << queryContent;
    if(!q.exec(queryContent))
        return false;
    return true;
}

void Entity::clear()
{
    _id = 0;
}

const QStringList& Entity::getData()
{
    _dataOut[Id] = QString::number(_id);
    return _dataOut;
}

void Entity::lineEdit_isEmpty_checker(const QString& s)
{
    auto lineEdit = qobject_cast<QLineEdit*>(sender());
    if(s.isEmpty())
    {
        lineEdit->setStyleSheet("border-bottom: 1px solid red;");
    }
    else
    {
        lineEdit->setStyleSheet("border-bottom: 1px solid grey;");
    }
}
