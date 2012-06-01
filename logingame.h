#ifndef LOGINGAME_H
#define LOGINGAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>

class loginGame : public QDialog
{
Q_OBJECT
public:
    loginGame(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~loginGame();

signals:
    void setLoginInfo(QString ip,QString port,int type);
public slots:
    void okBtnClick();
private:
    void initUi();
    QPushButton *ok;
    QLineEdit *hostIP;
    QLineEdit *hostPort;
    QComboBox *comboBox;
};

#endif // LOGIN_H
