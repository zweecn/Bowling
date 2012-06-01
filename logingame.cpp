#include "logingame.h"
#include <QMessageBox>
loginGame::loginGame(QWidget *parent, Qt::WindowFlags f) :
        QDialog(parent,f)
{
    initUi();
    connect(ok,SIGNAL(clicked()),this,SLOT(okBtnClick()));
    connect(ok,SIGNAL(clicked()),this,SLOT(close()));
}

void loginGame::okBtnClick()
{
    if(hostIP->text().isEmpty())
    {
        QMessageBox::information(0, tr("Client"),
                                 tr("host IP is empty."));
        return;
    }
    else if(hostPort->text().isEmpty())
    {
        QMessageBox::information(0, tr("Client"),
                                 tr("host port is empty."));
        return;
    }
    else
    {
        emit setLoginInfo(hostIP->text(),hostPort->text(),comboBox->currentIndex());
        close();
    }
}

void loginGame::initUi()
{
    this->resize(300, 371);
    this->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/2.png);"));
    comboBox=new QComboBox(this);
    comboBox->setGeometry(QRect(110,100,113,20));
    ok = new QPushButton(this);
    ok->setGeometry(QRect(180, 130, 93, 32));
    ok->setAutoFillBackground(false);
    ok->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/3.png);"));
    ok->setIconSize(QSize(93, 32));
    hostIP = new QLineEdit(this);
    hostIP->setGeometry(QRect(110, 30, 113, 20));
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Text, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
    QBrush brush1(QColor(118, 116, 108, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
    hostIP->setPalette(palette);
    comboBox->setPalette(palette);
    comboBox->addItem("顾客");
    comboBox->addItem("前台服务员");
    comboBox->addItem("其他人");
    hostPort = new QLineEdit(this);
    hostPort->setGeometry(QRect(110, 70, 113, 20));
    QPalette palette1;
    palette1.setBrush(QPalette::Active, QPalette::Text, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
    hostPort->setPalette(palette1);
}

loginGame::~loginGame()
{

}
