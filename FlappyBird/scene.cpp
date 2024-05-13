#include "scene.h"

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{
    setUpPillarTimer();
}

void Scene::setUpPillarTimer()
{
    pillarTimer=new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){


        PillarItem*pillarItem=new PillarItem();


        addItem(pillarItem);
    });

    pillarTimer -> start(1000);
}
