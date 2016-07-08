#ifndef MYBUTTON
#define MYBUTTON

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include "apperiance.h"

extern Apperiance *apperiance;

class MyButton:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    MyButton();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setHoverEvents(QBrush brushEnter, QBrush brushLeave);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void setGeometryOfButton(int x, int y, int width, int height);
    void setSizeOfButton(int width, int height);
    void setPositionOfButton(int x, int y);
    void setBrushOfButton(QBrush myBrush);
    void setFontOfButton(QFont font);
    void defineTextOfButton(QString text, QBrush myBrush, QFont font);
    void setTextOfButton(QString text);
    void setTextOfButtonPosition();

public slots:
    void quit();

signals:
    void clicked();
    void hoverEvent();

private:
    QBrush onHoverEventEnter, onHoverEventLeave;
    QGraphicsTextItem textToDisplay;
};

#endif // MYBUTTON
