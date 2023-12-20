#include "Relation.h"

Relation::Relation(const QString& attributeId, const QString& representingAttribute, const QString& tableName) :
    _attributeId{attributeId}, _representingAttribute{representingAttribute}, _tableName{tableName}
{}

const QStringList& Relation::getRelationValues() 
{
    _pKey_cbIndex.clear();
    _cbIndex_pKey.clear();
    _relationValues.clear();

    QSqlQuery q;
    q.prepare("SELECT " + _attributeId + " ," + _representingAttribute + " FROM " + _tableName);
    if(!q.exec())
    {
        qDebug() << "Relation(" + _attributeId + ", " + _representingAttribute + ", " + _tableName + " SQL ERROR";
        _relationValues.clear();
        return _relationValues;
    }
    for(int i = 0; i < q.size(); ++i)
    {
        q.next();
        auto pKey = q.value(0).toString();
        auto value = q.value(1).toString();
        _relationValues.push_back(value + " (" + pKey + ")");  
        _pKey_cbIndex[pKey.toInt()] = i + 1;
        _cbIndex_pKey[i + 1] = pKey.toInt(); 
    }
    return _relationValues;
}

int Relation::getPrimaryKeyByIndex(int index) const
{
    return _cbIndex_pKey[index]; 
}

int Relation::getIndexByPrimaryKey(int pKey) const
{
    return _pKey_cbIndex[pKey];
}

void Relation::loadComboBox(QComboBox* cb)
{
    cb->clear();
    cb->addItem("NULL");
    cb->addItems(this->getRelationValues());
}
