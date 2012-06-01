

#include "mazescene.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QPushButton>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <iostream>
#include <QHostAddress>

#include <qmath.h>
#include <qdebug.h>


#include "entity.h"


#ifndef QT_NO_OPENGL
#include <QGLWidget>
#endif

void View::resizeEvent(QResizeEvent *)
{
    resetMatrix();
    qreal factor = width() / 4.0;
    scale(factor, factor);
}

Light::Light(const QPointF &pos, qreal intensity)
    : m_pos(pos)
    , m_intensity(intensity)
{
}

qreal Light::intensityAt(const QPointF &pos) const
{
    const qreal quadraticIntensity = 150 * m_intensity;
    const qreal linearIntensity = 30 * m_intensity;

    const qreal d = QLineF(m_pos, pos).length();
    return quadraticIntensity / (d * d)
        + linearIntensity / d;
}

void MazeScene::setLoginInfo(QString hostAddress, QString port, int type1)
{
    hostIP=hostAddress;
    hostPort=port;
   entitiesPos->type=type1;
}
MazeScene::MazeScene(const QVector<Light> &lights, const char *map, int width, int height)
    : m_lights(lights)
    , m_walkingVelocity(0)
    , m_strafingVelocity(0)
    , m_turningSpeed(0)
    , m_pitchSpeed(0)
    , m_deltaYaw(0)
    , m_deltaPitch(0)
    , m_simulationTime(0)
    , m_walkTime(0)
    , m_width(width)
    , m_height(height)
    ,interval(0)

{

    entitiesPos=new EntitiesPosDate;
    tcp=new TcpControl(0);
    tcp->setEntitiesPosDate(entitiesPos);
    //connect(tcp,SIGNAL(updateEntities()),this,SLOT(updateEntitiesNum()));
    connect(tcp,SIGNAL(updateEntitiesPos()),this,SLOT(updateEntitiesPos()));
    loginClient=new loginGame(0,Qt::FramelessWindowHint);
    connect(loginClient,SIGNAL(setLoginInfo(QString,QString,int)),this,SLOT(setLoginInfo(QString,QString,int)));
    loginClient->exec();
    m_camera.setPos(QPointF(1.5, 1.5));
    m_camera.setYaw(49);

    m_doorAnimation = new QTimeLine(1000, this);
    m_doorAnimation->setUpdateInterval(20);
    connect(m_doorAnimation, SIGNAL(valueChanged(qreal)), this, SLOT(moveDoors(qreal)));

    QMap<char, int> types;
    types['?'] = -3;
    types[' '] = -2;
    types['-'] = -1;
    types['#'] = 0;
    types['&'] = 1;
    types['@'] = 2;
    types['%'] = 3;
    types['$'] = 4;
    types['!'] = 6;
    types['='] = 7;
    types['*'] = 8;
    types['('] = 9;

    int type;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            type = types[map[y*width+x]];
            if(type==-3)
            {
//                Entity *entity = new Entity(QPointF(x+0.5, y));
//                addEntity(entity);
            }
            if (type >= 0)
                continue;

            type = types[map[(y-1)*width+x]];
            if (type >= -1)
                addWall(QPointF(x, y), QPointF(x+1, y), type);

            type = types[map[(y+1)*width+x]];
            if (type >= -1)
                addWall(QPointF(x+1, y+1), QPointF(x, y+1), type);

            type = types[map[y*width+x-1]];
            if (type >= -1)
                addWall(QPointF(x, y+1), QPointF(x, y), type);

            type = types[map[y*width+x+1]];
            if (type >= -1)
                addWall(QPointF(x+1, y), QPointF(x+1, y+1), type);
        }
    }

    for(int i=6;i<19;i++)
    {
        addWall(QPointF(6,i),QPointF(6,i+0.5),5);
    }

    for(int i=5;i<12;i++)
    {
        addWall(QPointF(9,i),QPointF(9,i+1),2);
    }
    for(int i=9;i<12;i++)
    {
        addWall(QPointF(i,12),QPointF(i+1,12),2);
    }
    addWall(QPointF(10,5),QPointF(11,5),-1);
    addWall(QPointF(9,5),QPointF(10,5),3);

    QTimer *timer = new QTimer(this);
    timer->setInterval(20);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    m_time.start();
    updateTransforms();
    updateRenderer();
}

void MazeScene::addProjectedItem(ProjectedItem *item)
{
    addItem(item);
    m_projectedItems << item;
}

void MazeScene::addWall(const QPointF &a, const QPointF &b, int type)
{
    WallItem *item = new WallItem(this, a, b, type);


   /* QGraphicsProxyWidget *proxy = item->childItem();
    QWebView *view = proxy ? qobject_cast<QWebView *>(proxy->widget()) : 0;
    if (view) {


        connect(view, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished()));
        proxy->setVisible(false);
    }

*/
    item->setVisible(false);
    addProjectedItem(item);
    m_walls << item;

    if (type == -1)
        m_doors << item;

    setSceneRect(-1, -1, 2, 2);
    if (item->childItem()) {
        QObject *widget = item->childItem()->widget()->children().value(0);
        QPushButton *button = qobject_cast<QPushButton *>(widget);
        if (button)
            m_buttons << button;
    }
}

void MazeScene::loadFinished()
{
    QWidget *widget = qobject_cast<QWidget *>(sender());

    if (widget) {
        foreach (WallItem *item, m_walls) {
            QGraphicsProxyWidget *proxy = item->childItem();
            if (proxy && proxy->widget() == widget)
                proxy->setVisible(true);
        }
    }
}

static inline QTransform rotatingTransform(qreal angle)
{
    QTransform transform;
    transform.rotate(angle);
    return transform;
}

void Camera::setPitch(qreal pitch)
{
    m_pitch = qBound(qreal(-30), pitch, qreal(30));
    m_matrixDirty = true;
}

void Camera::setYaw(qreal yaw)
{
    m_yaw = yaw;
    m_matrixDirty = true;
}

void Camera::setPos(const QPointF &pos)
{
    m_pos = pos;
    m_matrixDirty = true;
}

void Camera::setFov(qreal fov)
{
    m_fov = fov;
    m_matrixDirty = true;
}

void Camera::setTime(qreal time)
{
    m_time = time;
    m_matrixDirty = true;
}


const Matrix4x4 &Camera::viewMatrix() const
{
    updateMatrix();
    return m_viewMatrix;
}

const Matrix4x4 &Camera::viewProjectionMatrix() const
{
    updateMatrix();
    return m_viewProjectionMatrix;
}

void Camera::updateMatrix() const
{
    if (!m_matrixDirty)
        return;

    m_matrixDirty = false;

    Matrix4x4 m;
    m *= Matrix4x4::fromTranslation(-m_pos.x(), 0.04 * qSin(10 * m_time) + 0.1, -m_pos.y());//qSin(10*m_time) 上纵效果
    m *= Matrix4x4::fromRotation(m_yaw + 180, Qt::YAxis);//水平视角
    m *= Matrix4x4::fromScale(-1, 1, 1);//翻转鼠标
    m *= Matrix4x4::fromRotation(m_pitch, Qt::XAxis);//竖直视角
    m_viewMatrix = m;
    m *= Matrix4x4::fromProjection(m_fov);
    m_viewProjectionMatrix = m;
}

void MazeScene::drawBackground(QPainter *painter, const QRectF &)
{
    static QImage floor = QImage("floor.png").convertToFormat(QImage::Format_RGB32);
    QBrush floorBrush(floor);

    static QImage ceiling = QImage("ceiling.png").convertToFormat(QImage::Format_RGB32);
    QBrush ceilingBrush(ceiling);

    static QImage blowingRow = QImage("blowingRow.png").convertToFormat(QImage::Format_RGB32);
    QBrush blowingRowBrush(blowingRow);

    QTransform brushScale;
    brushScale.scale(0.5 / floor.width(), 0.5 / floor.height());
    floorBrush.setTransform(brushScale);
    ceilingBrush.setTransform(brushScale);
    blowingRowBrush.setTransform(brushScale);

    const QRectF r(1, 1, m_width-2, m_height-2);
    QRectF r1(1,6,4,0.5);

    Matrix4x4 m = m_camera.viewProjectionMatrix();
    Matrix4x4 floorMatrix = Matrix4x4::fromRotation(90, Qt::XAxis);
    floorMatrix *= Matrix4x4::fromTranslation(0, 0.5, 0);//设置高度
    floorMatrix *= m;

    painter->save();
    painter->setTransform(floorMatrix.toQTransform(), true);
    painter->fillRect(r, floorBrush);//画地板
//    painter->restore();
//    painter->save();
//    painter->setTransform(floorMatrix.toQTransform(),true);
    for(int i=6;i<20;i++)
    {
        r1=QRectF(1,i,6,0.5);
        painter->fillRect(r1,blowingRowBrush);
    }

    painter->restore();

    Matrix4x4 ceilingMatrix = Matrix4x4::fromRotation(90, Qt::XAxis);
    ceilingMatrix *= Matrix4x4::fromTranslation(0, -0.5, 0);//设置高度
    ceilingMatrix *= m;

    painter->save();
    painter->setTransform(ceilingMatrix.toQTransform(), true);
    painter->fillRect(r, ceilingBrush);//画天花板
    painter->restore();
}

void MazeScene::addEntity(Entity *entity)
{
    addProjectedItem(entity);
    m_entities << entity;
}

ProjectedItem::ProjectedItem(const QRectF &bounds, bool shadow)
    : m_bounds(bounds)
    , m_shadowItem(0)
{
    if (shadow) {
        m_shadowItem = new QGraphicsRectItem(bounds, this);
        m_shadowItem->setPen(Qt::NoPen);
        m_shadowItem->setZValue(10);
    }

    m_targetRect = m_bounds;
}

void ProjectedItem::setPosition(const QPointF &a, const QPointF &b)
{
    m_a = a;
    m_b = b;
}

void ProjectedItem::setLightingEnabled(bool enable)
{
    if (m_shadowItem)
        m_shadowItem->setVisible(enable);
}

class ResizingView : public QGraphicsView
{
protected:
    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

class ProxyWidget : public QGraphicsProxyWidget
{
public:
    ProxyWidget(QGraphicsItem *parent = 0)
        : QGraphicsProxyWidget(parent)
    {
    }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant & value)
    {
        // we want the position of proxy widgets to stay at (0, 0)
        // so ignore the position changes from the native QWidget
        if (change == ItemPositionChange)
            return QPointF();
        else
            return QGraphicsProxyWidget::itemChange(change, value);
    }
};


WallItem::WallItem(MazeScene *scene, const QPointF &a, const QPointF &b, int type)
    : ProjectedItem(QRectF(-0.5, -0.5, 1.0, 1.0))
    , m_type(type)
{
    setPosition(a, b);

    static QImage brown = QImage("brown.png").convertToFormat(QImage::Format_RGB32);
    static QImage book = QImage("book.png").convertToFormat(QImage::Format_RGB32);
    static QImage door = QImage("door.png").convertToFormat(QImage::Format_RGB32);

    switch (type) {
    case -1:
        setImage(door);
        break;
    case 1:
        setImage(book);
        break;
    case 2:
        break;
    case 5:
        break;
    default:
        setImage(brown);
        break;
    }

    /*static const char *urls[] =
    {
        "http://www.google.com",
        "http://www.wikipedia.com",
        "http://programming.reddit.com",
        "http://www.trolltech.com",
        "http://www.planetkde.org",
        "http://labs.trolltech.com/blogs/"
    };
    */

    m_scale = 0.8;

    m_childItem = 0;
    QWidget *childWidget = 0;
    if (type == 3 && a.y() == b.y()) {
        QWidget *widget = new QWidget;
        QPushButton *button = new QPushButton("Open Sesame", widget);
        QObject::connect(button, SIGNAL(clicked()), scene, SLOT(toggleDoors()));
        widget->setLayout(new QVBoxLayout);
        widget->layout()->addWidget(button);
        childWidget = widget;
        m_scale = 0.3;
    } else if (type == 4) {
       Back *widget=new Back;
       childWidget=widget;
       m_scale = 1;
    } else if (type == 5) {
        Channel *widget=new Channel;
        scene->customerList.append(widget);
        widget->setPortAndID(4000+scene->customerList.size(),scene->customerList.size());
        childWidget=widget;
        m_scale = 0.9;
        }
     else if (type == 7) {
        MainFront *widget=new MainFront;
        childWidget=widget;
        scene->front=widget;
        m_scale = 1;
    } else if (type == 8) {
        Manager *widget=new Manager;
        childWidget=widget;
        m_scale=0.7;
    }
    else if (type == 9)
    {
        ATM *widget=new ATM;
        childWidget=widget;
        m_scale=1;
    }else if (type == 0 || type == 2) {
        /*static int index;
        if (index == 0) {
#ifndef QT_NO_OPENGL
            QWidget *widget = new QWidget;
            QCheckBox *checkBox = new QCheckBox("Use OpenGL", widget);
            checkBox->setChecked(true);
            QObject::connect(checkBox, SIGNAL(toggled(bool)), scene, SLOT(toggleRenderer()), Qt::QueuedConnection);
            widget->setLayout(new QVBoxLayout);
            widget->layout()->addWidget(checkBox);
            childWidget = widget;
            m_scale = 0.2;
#endif
        }
        else if (!(index % 7)) {
            static int webIndex = 0;
            const char *url = urls[webIndex++ % (sizeof(urls)/sizeof(char*))];

            QWebView *view = new QWebView;
            view->setUrl(QUrl(url));

            childWidget = view;
        }

        ++index;*/
    }

    if (!childWidget)
        return;

    childWidget->installEventFilter(scene);

    m_childItem = new ProxyWidget(this);
    m_childItem->setWidget(childWidget);
    m_childItem->setCacheMode(QGraphicsItem::ItemCoordinateCache);

    QRectF rect = m_childItem->boundingRect();
    QPointF center = rect.center();

    qreal scale = qMin(m_scale / rect.width(), m_scale / rect.height());
    m_childItem->translate(0, -0.05);
    m_childItem->scale(scale, scale);
    m_childItem->translate(-center.x(), -center.y());
}

bool MazeScene::eventFilter(QObject *target, QEvent *event)
{
    QWidget *widget = qobject_cast<QWidget *>(target);
    if (!widget || event->type() != QEvent::Resize)
        return false;

    foreach (WallItem *item, m_walls) {
        QGraphicsProxyWidget *proxy = item->childItem();
        if (proxy && proxy->widget() == widget)
            item->childResized();
    }

    return false;
}

void WallItem::childResized()
{
    QRectF rect = m_childItem->boundingRect();

    QPointF center = rect.center();

    qreal scale = qMin(m_scale / rect.width(), m_scale / rect.height());
    m_childItem->resetMatrix();
    m_childItem->translate(0, -0.05);
    m_childItem->scale(scale, scale);
    m_childItem->translate(-center.x(), -center.y());

    // refresh cache size
    m_childItem->setCacheMode(QGraphicsItem::NoCache);
    m_childItem->setCacheMode(QGraphicsItem::ItemCoordinateCache);
}

void ProjectedItem::updateLighting(const QVector<Light> &lights, bool useConstantLight)
{
    if (!m_shadowItem)
        return;

    if (useConstantLight) {
        m_shadowItem->setBrush(QColor(0, 0, 0, 100));
        return;
    }

    const qreal constantIntensity = 80;
    qreal la = constantIntensity;
    qreal lb = constantIntensity;
    foreach (const Light &light, lights) {
        la += light.intensityAt(m_b);
        lb += light.intensityAt(m_a);
    }

    int va = qMax(0, 255 - int(la));
    int vb = qMax(0, 255 - int(lb));

    if (va == vb) {
        m_shadowItem->setBrush(QColor(0, 0, 0, va));
    } else {
        const QRectF rect = boundingRect();
        QLinearGradient g(rect.topLeft(), rect.topRight());

        g.setColorAt(0, QColor(0, 0, 0, va));
        g.setColorAt(1, QColor(0, 0, 0, vb));

        m_shadowItem->setBrush(g);
    }
}

QRectF ProjectedItem::boundingRect() const
{
    return m_bounds;
}

void ProjectedItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!m_image.isNull()) {
        QRectF target = m_targetRect.translated(0.5, 0.5);
        QRectF source = QRectF(0, 0, m_image.width() * (1 - target.x()), m_image.height());
        painter->drawImage(m_targetRect, m_image, source);
    }
}

void ProjectedItem::setAnimationTime(qreal time)
{
    // hacky way of handling door animation
    QRectF rect = boundingRect();
    m_targetRect = QRectF(QPointF(rect.left() + rect.width() * time, rect.top()),
                          rect.bottomRight());
    if (m_shadowItem)
        m_shadowItem->setRect(m_targetRect);
    update();
}

void ProjectedItem::setImage(const QImage &image)
{
    m_image = image;
    update();
}

void ProjectedItem::updateTransform(const Camera &camera)
{
    QTransform rotation;
    rotation *= QTransform().translate(-camera.pos().x(), -camera.pos().y());
    rotation *= rotatingTransform(camera.yaw());
    QPointF center = (m_a + m_b) / 2;

    QPointF ca = rotation.map(m_a);
    QPointF cb = rotation.map(m_b);

    if (ca.y() <= 0 && cb.y() <= 0) {
        // hide the item by placing it far outside the scene
        // we could use setVisible() but that causes unnecessary
        // update to cahced items
        QTransform transform;
        transform.translate(-1000, -1000);
        setTransform(transform);
        return;
    }

    Matrix4x4 m;
    m *= Matrix4x4::fromRotation(-QLineF(m_b, m_a).angle(), Qt::YAxis);
    m *= Matrix4x4::fromTranslation(center.x(), 0, center.y());
    m *= camera.viewProjectionMatrix();

    qreal zm = QLineF(camera.pos(), center).length();

    setVisible(true);
    setZValue(-zm);
    setTransform(m.toQTransform());
}


void MazeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (focusItem()) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    if (event->buttons() & Qt::RightButton) {
        QPointF delta(event->scenePos() - event->lastScenePos());
        m_deltaYaw += delta.x() * 80;
        m_deltaPitch -= delta.y() * 80;
//        foreach (Entity *entity, m_entities)
//        {
//            entity->turnTowards();
//        }
    }
}

void MazeScene::keyPressEvent(QKeyEvent *event)
{
    if (handleKey(event->key(), true)) {
        event->accept();
        return;
    }

    QGraphicsScene::keyPressEvent(event);
}

void MazeScene::keyReleaseEvent(QKeyEvent *event)
{
    if (handleKey(event->key(), false)) {
        event->accept();
        return;
    }

    QGraphicsScene::keyReleaseEvent(event);
}

bool MazeScene::handleKey(int key, bool pressed)
{
    if (focusItem())
        return false;

    switch (key) {
    case Qt::Key_Left:
    case Qt::Key_Q:
        m_turningSpeed = (pressed ? -0.5 : 0.0);
        return true;
    case Qt::Key_Right:
    case Qt::Key_E:
        m_turningSpeed = (pressed ? 0.5 : 0.0);
        return true;
    case Qt::Key_Down:
        m_pitchSpeed = (pressed ? 0.5 : 0.0);
        return true;
    case Qt::Key_Up:
        m_pitchSpeed = (pressed ? -0.5 : 0.0);
        return true;
    case Qt::Key_S:
        m_walkingVelocity = (pressed ? -0.01 : 0.0);
        return true;
    case Qt::Key_W:
        m_walkingVelocity = (pressed ? 0.01 : 0.0);
        return true;
    case Qt::Key_A:
        m_strafingVelocity = (pressed ? -0.01 : 0.0);
        return true;
    case Qt::Key_D:
        m_strafingVelocity = (pressed ? 0.01 : 0.0);
        return true;
    }

    return false;
}

static inline QRectF rectFromPoint(const QPointF &point, qreal size)
{
    return QRectF(point, point).adjusted(-size/2, -size/2, size/2, size/2);
}

bool MazeScene::blocked(const QPointF &pos, Entity *me) const
{
    const QRectF rect = rectFromPoint(pos, me ? 0.7 : 0.25);

    foreach (WallItem *item, m_walls) {
        if (item->type() == 6
            || item->type() == -1 && m_doorAnimation->state() != QTimeLine::Running
               && m_doorAnimation->direction() == QTimeLine::Backward)
            continue;

        const QPointF a = item->a();
        const QPointF b = item->b();

        QRectF wallRect = QRectF(a, b).adjusted(-0.01, -0.01, 0.01, 0.01);

        if (wallRect.intersects(rect))
            return true;
    }

//    foreach (Entity *entity, m_entities) {
//        if (entity == me)
//            continue;
//        QRectF entityRect = rectFromPoint(entity->pos(), 0.8);
//
//        if (entityRect.intersects(rect))
//            return true;
//    }
//
//    if (me) {
//        QRectF cameraRect = rectFromPoint(m_camera.pos(), 0.4);
//
//        if (cameraRect.intersects(rect))
//            return true;
//    }

    return false;
}

bool MazeScene::tryMove(QPointF &pos, const QPointF &delta, Entity *entity) const
{
    const QPointF old = pos;

    if (delta.x() != 0 && !blocked(pos + QPointF(delta.x(), 0), entity))
        pos.setX(pos.x() + delta.x());

    if (delta.y() != 0 && !blocked(pos + QPointF(0, delta.y()), entity))
        pos.setY(pos.y() + delta.y());

    return pos != old;
}

void MazeScene::updateTransforms()
{
    foreach (ProjectedItem *item, m_projectedItems)
        item->updateTransform(m_camera);

    /*foreach (WallItem *item, m_walls) {
        if (item->isVisible()) {
            // embed recursive scene
            if (QGraphicsProxyWidget *child = item->childItem()) {
                View *view = qobject_cast<View *>(child->widget());
                if (view && !view->scene()) {
                    const char *map =
                        "#$###"
                        "#   #"
                        "# @ #"
                        "#   #"
                        "#####";
                    QVector<Light> lights;
                    lights << Light(QPointF(2.5, 2.5), 1)
                           << Light(QPointF(1.5, 1.5), 0.4);
                    MazeScene *embeddedScene = new MazeScene(lights, map, 5, 5);
                    view->setScene(embeddedScene);
                    view->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
                }
            }
        }
    }*/

    setFocusItem(0); // setVisible(true) might give focus to one of the items
    update();
}

void MazeScene::move()
{
    QSet<Entity *> movedEntities;
    long elapsed = m_time.elapsed();
    bool walked = false;

    const int stepSize = 5;
    int steps = (elapsed - m_simulationTime) / stepSize;
    if (steps) {
        m_deltaYaw /= steps;
        m_deltaPitch /= steps;

        m_deltaYaw += m_turningSpeed;
        m_deltaPitch += m_pitchSpeed;
    }

    for (int i = 0; i < steps; ++i) {
        m_camera.setYaw(m_camera.yaw() + m_deltaYaw);
        m_camera.setPitch(m_camera.pitch() + m_deltaPitch);

        bool walking = false;
        if(interval==50)
        {
            interval=0;
        tcp->connectToServer(hostIP,hostPort.toInt(),QPointF(m_camera.pos().x(),m_camera.pos().y()));
        }
        interval++;
        if (m_walkingVelocity != 0) {
            QPointF walkingDelta = QLineF::fromPolar(m_walkingVelocity, m_camera.yaw() - 90).p2();
            QPointF pos = m_camera.pos();
            if (tryMove(pos, walkingDelta)) {
                walking = true;
//                foreach(Entity *entity, m_entities)
//                {
//                        entity->walk();
//                        entity->turnTowards(m_camera.pos().x(),m_camera.pos().y());
//                }
//                if(interval==50)
//                {
//                    interval=0;
//                tcp->connectToServer(hostIP,hostPort.toInt(),QPointF(m_camera.pos().x(),m_camera.pos().y()));
//                }
//                interval++;
                m_camera.setPos(pos);
            }
        }

        if (m_strafingVelocity != 0) {
            QPointF walkingDelta = QLineF::fromPolar(m_strafingVelocity, m_camera.yaw()).p2();
            QPointF pos = m_camera.pos();
            if (tryMove(pos, walkingDelta)) {
                walking = true;
//                foreach(Entity *entity, m_entities)
//                {
//                        entity->walk();
//                        entity->turnTowards(m_camera.pos().x(),m_camera.pos().y());
//                }

                m_camera.setPos(pos);
            }
        }

        walked = walked || walking;

        if (walking)
            m_walkTime += stepSize;
        m_simulationTime += stepSize;

        foreach (Entity *entity, m_entities) {
            qreal dx=entity->player_pos.x()-entity->pos().x();
            qreal dy=entity->player_pos.y()-entity->pos().y();
            if(dx*dx+dy*dy<0.3)
            {
                entity->stop();
            }
            if (entity->move(this))
                movedEntities.insert(entity);
        }
    }

    m_camera.setTime(m_walkTime * 0.001);

    if (walked || m_deltaYaw != 0 || m_deltaPitch != 0) {
        updateTransforms();
    } else {
        foreach (Entity *entity, movedEntities)
        {
            entity->updateTransform(m_camera);
        }
    }

    if (steps) {
        m_deltaYaw = 0;
        m_deltaPitch = 0;
    }
}

void MazeScene::toggleDoors()
{
    setFocusItem(0);

    if (m_doorAnimation->state() == QTimeLine::Running)
        return;

    foreach (QPushButton *button, m_buttons) {
        if (m_doorAnimation->direction() == QTimeLine::Forward)
            button->setText("Close Sesame!");
        else
            button->setText("Open Sesame!");
    }

    m_doorAnimation->toggleDirection();
    m_doorAnimation->start();
}

void MazeScene::moveDoors(qreal value)
{
    foreach (WallItem *item, m_doors)
        item->setAnimationTime(1 - value);
}

void MazeScene::toggleRenderer()
{
#ifndef QT_NO_OPENGL
    if (views().size() == 0)
        return;
    QGraphicsView *view = views().at(0);
    if (view) {
        view->setViewport(
                view->viewport()->inherits("QGLWidget")
                ? new QWidget
                : new QGLWidget(QGLFormat(QGL::SampleBuffers)));

        updateRenderer();
    }
#endif
}

void MazeScene::updateRenderer()
{
    QGraphicsView *view = views().isEmpty() ? 0 : views().at(0);
    bool accelerated = view && view->viewport()->inherits("QGLWidget");
    if (view) {
        if (accelerated)
            view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        else
            view->setRenderHints(QPainter::Antialiasing);
    }

    foreach (WallItem *item, m_walls)
        item->updateLighting(m_lights, item->type() == 2);
}

int MazeScene::getNumberOfEntities()
{
    return m_entities.size();
}

void MazeScene::sendEntitiesMessage()
{
    QPointF pos;
    foreach(Entity *entity, m_entities)
    {
            entity->walk();
            pos=entitiesPos->entitiesPosInfo.value(entity->ID);
            entity->turnTowards(pos.x(),pos.y());
    }
}



void MazeScene::updateEntitiesPos()
{
    bool dirty=true;
    QPointF tmpPos;
    QMap<QString, QPointF>::const_iterator i = entitiesPos->entitiesPosInfo.constBegin();
     while (i != entitiesPos->entitiesPosInfo.constEnd()) {
         tmpPos=i.value();
         for(int j=0;j<m_entities.size();j++)
         {
                 if(!m_entities[j]->ID.compare(i.key()))
                {
                     m_entities[j]->walk();
                     m_entities[j]->setPlayerPos(tmpPos);
                    m_entities[j]->turnTowards(tmpPos.x(),tmpPos.y());
                    dirty=false;
                    break;
                 }



         }
         if(dirty)
         {
         Entity *entity = new Entity(i.value());
         entity->ID=i.key();
         addEntity(entity);
     }
         dirty=true;
         ++i;
     }
}
