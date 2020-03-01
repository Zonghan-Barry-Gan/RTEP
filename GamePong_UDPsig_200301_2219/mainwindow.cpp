#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "gameplay.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

const quint16 rsPort = 1112;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iScore ( 0 ),
    iBallMotion ( -0.5, -0.5 ),
    iP2Motion( 0 ),
    iP1Motion( 0 )
{
    ui->setupUi(this);

    iScene = new QGraphicsScene(this);

    iP2 = new QGraphicsRectItem(0, 0, 80, 20);
    iP2->setBrush(QBrush(Qt::blue));
    iP1 = new QGraphicsRectItem(0, 0, 80, 20);
    iP1->setBrush(QBrush(Qt::green));

    iBall = new QGraphicsEllipseItem(0, 0, 15, 15);
    iBall->setBrush(QBrush(Qt::magenta));

    ui->boardView->setScene(iScene);


    iTimer = new QTimer(this);
    iTimer->setInterval(2);
    //condition of timer start
    iTimer->start();
    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(Position()));


    iScene->setSceneRect(0, 0, 350, 320);
    iScene->addItem(iP2);
    iScene->addItem(iP1);
    iScene->addItem(iBall);

    iP2->setPos(135, 5);
    iP1->setPos(135, 300);
    iBall->setPos(150, 150);







    QSize m(iScene->sceneRect().size().width() + 10, iScene->sceneRect().size().height() + 10);
    ui->boardView->setMinimumSize(m);

    resize(minimumSize());


    QObject::connect(this, SIGNAL(goal(int)),this, SLOT(refreshScore(int)));

    QObject::connect(this, SIGNAL(P2isleft()),this, SLOT(P2Moveleft()));
    QObject::connect(this, SIGNAL(P2isright()),this, SLOT(P2Moveright()));


//receive udp sig
    rsverSocket = new QUdpSocket;
    //bind local address and port for receiving
    //local address
    //bool bdrsvsc = rsverSocket->bind(QHostAddress("172.30.141.244"), rsPort);
    bool bdrsvsc = rsverSocket->bind(QHostAddress("127.0.0.1"), rsPort);

    //bool bdrsvsc = rsverSocket->bind(QHostAddress::LocalHost, rsPort);
    if(bdrsvsc>0)
      { qDebug()<<"bind success";
        qDebug() << "--- receiving--";
    }
    else
    {
        qDebug()<<"bind failed";
        qDebug()<<rsverSocket->error();
    }
    connect(rsverSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete rsverSocket;
}

void MainWindow::refreshScore(int count)
{
    iScore += count;
    ui->lcdNumber->display(iScore);
}

void MainWindow::Position()
{
    qreal Xprime = iBall->pos().x() + iBallMotion.x();
    qreal Yprime = iBall->pos().y() + iBallMotion.y();

    qreal P2Xprime = iP2->pos().x() + iP2Motion;
    qreal P1Xprime = iP1->pos().x() + iP1Motion;

    if ( ( Xprime < 0 ) || ( Xprime + iBall->boundingRect().right() > iScene->sceneRect().right() ) )
    {
        iBallMotion.rx() *= -1;
    }

    if ( ( Yprime < 0 ) || ( Yprime + iBall->boundingRect().bottom() > iScene->sceneRect().bottom() ) )
    {
        // 1 for hitting the bottom wall, -1 for hitting the top wall
        emit goal(Yprime / abs(Yprime));
        iBallMotion.ry() *= -1;
    }

    if ( ( P2Xprime < 0 ) || ( P2Xprime + iP2->boundingRect().right() > iScene->sceneRect().right() ) )
    {
        iP2Motion = 0;
    }

    if ( ( P1Xprime < 0 ) || ( P1Xprime + iP2->boundingRect().right() > iScene->sceneRect().right() ) )
    {
        iP1Motion = 0;
    }

    if ( ( iP2->collidesWithItem(iBall) ) && ( iBallMotion.y() < 0 ) )
    {
        iBallMotion.ry() *= -1;
    }

    if ( ( iP1->collidesWithItem(iBall) ) && ( iBallMotion.y() > 0 ) )
    {
        iBallMotion.ry() *= -1;
    }

    if ( qrand() % 10 == 0 )
    {
        iP1Motion = CpuP1Motion();
    }


    iBall->moveBy(iBallMotion.x(), iBallMotion.y());
    iP2->moveBy(iP2Motion, 0);
    iP1->moveBy(iP1Motion, 0);
}


qreal MainWindow::CpuP1Motion()
{
    qreal dir = 0;

    if ( iBall->pos().x() + iBallMotion.x() > iP1->sceneBoundingRect().right() )
    {
        // move right
        dir = 5.0/6.0;
    }
    else if ( iBall->pos().x() + iBallMotion.x() < iP1->sceneBoundingRect().left() )
    {
        // move left
        dir = -5.0/6.0;
    }

    return dir;

}
void MainWindow::P2Moveright()
{
    iP2Motion  = (iP2Motion == 0 ? 2 : 0);
    qDebug()<<"move right";
}
void MainWindow::P2Moveleft()
{
    iP2Motion = (iP2Motion == 0 ? -2 : 0);
    qDebug()<<"move left";
}


void MainWindow::receive()
{
    QByteArray dtstrm;
    while(rsverSocket->hasPendingDatagrams())
    {
        dtstrm.resize(rsverSocket->pendingDatagramSize());
        rsverSocket->readDatagram(dtstrm.data(), dtstrm.size());

        bool cktP1;
        const float outval= dtstrm.toFloat(&cktP1);
        if (!cktP1) qDebug() << "received but data error, data type Conversion failed";
// //test outvalue
//        qDebug() << "data: " << outval;
        if (outval<0) emit P2isleft();
        else if (outval>0)
        {
            emit P2isright();
        }
    }
}
