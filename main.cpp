#include <QtSql>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <QtGui>
#include "mazescene.h"
#include "tcpcontrol.h"
bool createConnection();
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("gb2312");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    app.setApplicationName("bowling");
    QPixmapCache::setCacheLimit(100 * 1024); // 100 MB
    if (!createConnection())
            return -1;

    const char *map =
            "#####=######"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          *"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          #"
            "#          $"
            "#          #"
            "#          #"
            "#######(####";

    QVector<Light> lights;
    lights << Light(QPointF(3.5, 2.5), 1)
           << Light(QPointF(3.5, 6.5), 1)
           << Light(QPointF(1.5, 10.5), 0.3);

    MazeScene *scene = new MazeScene(lights, map, 12, 20);

    View view;
    view.resize(800, 600);
    view.setScene(scene);
    view.show();

    scene->toggleRenderer();

    return app.exec();
}

bool createConnection()
{
    QFile file("database.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open database.txt";
           return false;
       }
    QTextStream in(&file);
    QList<QString> parameter;
    while (!in.atEnd())
    {
         QString line = in.readLine();
         parameter.append(line);
    }

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(parameter[0]);
    db.setPort(parameter[1].toInt());
        db.setDatabaseName("bowling");
        db.setUserName("root");
        db.setPassword("123456");
        if (!db.open())
        {
                QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
                return false;
        }
        return true;
}
