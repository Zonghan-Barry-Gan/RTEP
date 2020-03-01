#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QObject>
#include <QUdpSocket>

class QGraphicsItem;
class QTimer;

class Gameplay;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    Gameplay *iLoop;
    int iScore;

    //graphic item in gameplay
    QGraphicsScene * iScene;
    QGraphicsRectItem *iP2, *iP1;
    QGraphicsEllipseItem *iBall;
    QTimer *iTimer;

    QPointF iBallMotion;
    qreal iP2Motion;
    qreal iP1Motion;
    qreal CpuP1Motion();
    //QUdpSocket *rsverSocket;
public slots:
    void refreshScore(int count);
    void Position();
    void P2Moveleft();
    void P2Moveright();



signals:
    void goal(int player);
    void P2isleft();
    void P2isright();


//for udp receive
public slots:
    void receive();

private:
    QUdpSocket *rsverSocket;
};

#endif // MAINWINDOW_H
