#ifndef ENTITIESPOSDATE_H
#define ENTITIESPOSDATE_H
#include <QMap>
#include <QString>
#include <QPointF>
#include <QList>

struct updateNode
{
    QString id;
    QPointF pos;
};
class EntitiesPosDate
{
public:
    EntitiesPosDate();
    QMap<QString,QPointF> entitiesPosInfo;
    QList<updateNode> updateInfo;
    int type;
};

#endif // ENTITIESPOSDATE_H
