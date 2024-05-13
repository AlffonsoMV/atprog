#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>>
#include <QTimer>
#include "pillaritem.h"


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

signals:

public slots:
private:
    void setUpPillarTimer();

    QTimer*pillarTimer;
};

#endif // SCENE_H
