#ifndef CHANNEL_H
#define CHANNEL_H

#include <QtGui/QWidget>

class channel : public QWidget
{
    Q_OBJECT

public:
    channel(QWidget *parent = 0);
    ~channel();
};

#endif // CHANNEL_H
