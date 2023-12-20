#ifndef RELATION_H
#define RELATION_H

#include <QHash>
#include <QVector>
#include <QString>
#include <QComboBox>
#include <QSqlQuery>

enum RelationParts{
    ViewAttribute,
    TableAttribute,
    TableName
};

typedef QHash<int, int> hash_table;

class Relation
{
public:
    Relation(const QString& attributeId, const QString& representingAttribute, const QString& tableName);

    Relation(const Relation& r) = delete;

    int getPrimaryKeyByIndex(int index) const;

    int getIndexByPrimaryKey(int pKey) const;

    const QStringList& getRelationValues();

    void loadComboBox(QComboBox* cb);

private:
    hash_table _pKey_cbIndex;
    hash_table _cbIndex_pKey;
    QStringList _relationValues;

    QString _attributeId;
    QString _representingAttribute;
    QString _tableName;
};

#endif // RELATION_H
