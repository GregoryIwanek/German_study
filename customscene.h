#ifndef CUSTOMSCENE
#define CUSTOMSCENE
#include <QPainter>
#include <QGraphicsScene>
#include <QMainWindow>

class CustomScene:public QGraphicsScene{
    Q_OBJECT

public:
    CustomScene(QObject *parent=0);
    QPointF getGridPoint(QPointF point);
    int getGridSize();

private:
    int gridSize;

protected:
    void drawBackgroundGrid(QPainter *painter, const QRectF &rect);
};

#endif // CUSTOMSCENE
