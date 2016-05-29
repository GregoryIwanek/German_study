#include "customscene.h"
#include <QDebug>

CustomScene::CustomScene(QObject *parent): QGraphicsScene(parent), gridSize(20)
{

}

int CustomScene::getGridSize()
{
    return gridSize;
}

QPointF CustomScene::getGridPoint(QPointF point)
{
    qreal xV = round(point.x()/gridSize)*gridSize;
    qreal yV = round(point.y()/gridSize)*gridSize;
    return QPointF(xV,yV);
}

void CustomScene::drawBackgroundGrid(QPainter *painter, const QRectF &rect)
{
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);

    double left = int(rect.left()) - (int(rect.left()) % gridSize);
    double top = int(rect.top()) - (int(rect.top()) % gridSize);

    QVector<QPointF> points;
    for (double x = left; x < rect.right(); x += gridSize){
        for (double y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(),points.size());
}
