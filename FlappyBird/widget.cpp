#include "widget.h"
#include "./ui_widget.h"
#include <QGraphicsPixmapItem>
#include "pillaritem.h"
#include "../src/Solvers/BacktrackingSolver.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene-> setSceneRect(-250,-300,500,00);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/images/board.png"));
    scene -> addItem(pixItem);
    pixItem->setPos(QPointF(0,0)-QPointF(pixItem->boundingRect().width()/2,pixItem->boundingRect().height()/2));

    scene -> addLine(-400,0,400,0,QPen(Qt::blue));
    scene -> addLine(0,-400,0,400,QPen(Qt::blue));


//    PillarItem*pillar = new PillarItem();
//    scene -> addItem(pillar);

    ui -> graphicsView -> setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}
