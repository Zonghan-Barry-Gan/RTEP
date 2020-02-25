#ifndef UDPRSVERTEST_H
#define UDPRSVERTEST_H

#include <QObject>
#include <QUdpSocket>

class Udprsvertest : public QObject
{
    Q_OBJECT

public:
    Udprsvertest(QObject *p = 0);
    ~Udprsvertest();

public slots:
    void receive();

private:
    QUdpSocket *rsverSocket;
};

#endif // UDPRSVERTEST_H
//inspired by https://www.bogotobogo.com/Qt/Qt5_QUdpSocket.php
