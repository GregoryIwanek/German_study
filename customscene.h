#ifndef CUSTOMSCENE
#define CUSTOMSCENE
#include <QPainter>
#include <QGraphicsScene>
#include <QMainWindow>

class CustomScene:public QGraphicsScene{
    Q_OBJECT
public:
    CustomScene(QObject *parent=0);
    int const getGridSize();
    QPointF getGridPoint(QPointF point);
private:
    int gridSize;
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // CUSTOMSCENE
