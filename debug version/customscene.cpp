#include "customscene.h"
#include <QDebug>

CustomScene::CustomScene(QObject *parent): QGraphicsScene(parent), gridSize(20)
{

}

void CustomScene::drawBackgroundGrid(QPainter *painter, const QRectF &rect)
{
    //define custom scene with grid of points every 20pixels

    //define pen to draw points
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);

    //setting starting point of grid
    double left = int(rect.left()) - (int(rect.left()) % gridSize);
    double top = int(rect.top()) - (int(rect.top()) % gridSize);

    //adds coordinates of points of grid to vector
    QVector<QPointF> points;
    for (double x = left; x < rect.right(); x += gridSize){
        for (double y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }

    //paint points of grid stored in vector
    painter->drawPoints(points.data(),points.size());
}

QPointF CustomScene::getGridPoint(QPointF point)
{
    //return closest grid point to given coordinates
    qreal xV = round(point.x()/gridSize)*gridSize;
    qreal yV = round(point.y()/gridSize)*gridSize;
    return QPointF(xV,yV);
}

int CustomScene::getGridSize()
{
    return gridSize;
}
