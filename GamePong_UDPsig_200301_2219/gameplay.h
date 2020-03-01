#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>
#include <QGraphicsScene>
class QGraphicsItem;
class QTimer;

class Gameplay : public QObject
{
    Q_OBJECT
public:
    explicit Gameplay(QGraphicsScene & scene, QGraphicsItem *p1, QGraphicsItem *p2, QGraphicsItem *ball, QObject *parent);
    QGraphicsScene & iScene;
    QGraphicsItem *iP1, *iP2, *iBall;
    QTimer *iTimer;

    QPointF iBallDirection;
    qreal iP1Direction;
    qreal iP2Direction;

    virtual bool eventFilter(QObject *, QEvent *);
    qreal calculateP2Direction();

signals:
    //void goal(int player);

    //moved to mainwindow
public slots:
    //void tick();


};

#endif // GAMEPLAY_H
