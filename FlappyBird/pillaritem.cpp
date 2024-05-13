#include "pillaritem.h"
#include <QRandomGenerator>
#include<QGraphicsScene>

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/queenfin.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/queenfin.png")))
{
    topPillar -> setPos(QPoint(0,0)-QPoint(topPillar->boundingRect().width()/2,topPillar->boundingRect().height()+60));
    bottomPillar -> setPos(QPointF(0,0)+QPointF(-bottomPillar->boundingRect().width()/2,60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    int yPos = QRandomGenerator::global() -> bounded(150);
    int xRandomizer= QRandomGenerator::global() -> bounded(200);

    setPos(QPoint(0,0)+QPoint(260+xRandomizer,yPos));


    xAnimation = new QPropertyAnimation(this,"x",this);
    xAnimation -> setStartValue(260+xRandomizer);
    xAnimation -> setEndValue(-260);
    xAnimation -> setEasingCurve(QEasingCurve::Linear);
    xAnimation -> setDuration(1500);


    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        scene() -> removeItem(this);
        delete this;
    });


    xAnimation -> start();


}



qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setx(qreal newX)
{

    m_x = newX;
}
