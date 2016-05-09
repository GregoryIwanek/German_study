#include "mybutton.h"
#include <QGraphicsView>
#include <QDebug>

MyButton::MyButton()
{
}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void MyButton::setHoverEvents(QBrush brushEnter, QBrush brushLeave)
{
    this->setAcceptHoverEvents(true);
    onHoverEventEnter = brushEnter;
    onHoverEventLeave = brushLeave;
}

void MyButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(onHoverEventEnter);
}

void MyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(onHoverEventLeave);
}

void MyButton::setGeometryOfButton(int x, int y, int width, int height)
{
    setSizeOfButton(width, height);
    setPositionOfButton(x, y);
}

void MyButton::setSizeOfButton(int width, int height)
{
    setRect(0,0,width,height);
}

void MyButton::setPositionOfButton(int x, int y)
{
    setPos(x,y);
}

void MyButton::setBrushOfButton(QBrush myBrush)
{
    setBrush(myBrush);

}

void MyButton::setFontOfButton(QFont font)
{
    textToDisplay.setFont(font);
}

void MyButton::defineTextOfButton(QString text, QBrush myBrush, QFont font)
{
    setTextOfButton(text);
    setBrushOfButton(myBrush);
    setFontOfButton(font);
    setTextOfButtonPosition();
}

void MyButton::setTextOfButton(QString text)
{
    textToDisplay.setPlainText(text);
    textToDisplay.setParentItem(this);
}

void MyButton::setTextOfButtonPosition()
{
    int x = this->boundingRect().width()/2 - textToDisplay.boundingRect().width()/2;
    int y = this->boundingRect().height()/2 - textToDisplay.boundingRect().height()/2;
    textToDisplay.setPos(x,y);
}

void MyButton::quit()
{
}
