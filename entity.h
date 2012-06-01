

#ifndef ENTITY_H
#define ENTITY_H

#include <QPointF>
#include <QObject>

#include "mazescene.h"

class Entity : public QObject, public ProjectedItem
{
    Q_OBJECT
public:
    Entity(const QPointF &pos);
    void updateTransform(const Camera &camera);

    QPointF pos() const { return m_pos; }
    void setPlayerPos(QPointF pos);
    bool move(MazeScene *scene);
    QString ID;
    QPointF player_pos;
public slots:
    void turnTowards(qreal x, qreal y);
    void turnLeft();
    void turnRight();
    void walk();
    void stop();

protected:
    void timerEvent(QTimerEvent *event);

private:
    void updateImage();

private:
    QPointF m_pos;

    qreal m_angle;
    bool m_walking;
    bool m_walked;

    qreal m_turnVelocity;
    QPointF m_turnTarget;

    bool m_useTurnTarget;

    int m_animationIndex;
    int m_angleIndex;
};

#endif
