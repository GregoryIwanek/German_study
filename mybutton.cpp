#include "mybutton.h"
#include <QGraphicsView>
#include <QDebug>

MyButton::MyButton()
{
}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //event after click on button
    emit clicked();
}

void MyButton::setHoverEvents(QBrush brushEnter, QBrush brushLeave)
{
    //sets change of color of the button when we move mouse in/out possible
    this->setAcceptHoverEvents(true);

    //sets brushesh to change color
    onHoverEventEnter = brushEnter;
    onHoverEventLeave = brushLeave;
}

void MyButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //color on enter
    this->setBrush(onHoverEventEnter);
    emit hoverEvent();
}

void MyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //color after leave
    this->setBrush(onHoverEventLeave);
    emit hoverEvent();
}

void MyButton::setGeometryOfButton(int x, int y, int width, int height)
{
    //sets size and position of button inside a scene
    setSizeOfButton(width, height);
    setPositionOfButton(x, y);
}

void MyButton::setSizeOfButton(int width, int height)
{
    //size
    setRect(0,0,width,height);
}

void MyButton::setPositionOfButton(int x, int y)
{
    //position
    setPos(x,y);
}

void MyButton::defineTextOfButton(QString text, QBrush myBrush, QFont font)
{
    //steps to define text in butoon
    setTextOfButton(text);
    setBrushOfButton(myBrush);
    setFontOfButton(font);
    setTextOfButtonPosition();
}

void MyButton::setBrushOfButton(QBrush myBrush)
{
    //sets color of button
    setBrush(myBrush);
}

void MyButton::setFontOfButton(QFont font)
{
    //sets default font size of text
    textToDisplay.setFont(font);
}

void MyButton::setTextOfButton(QString text)
{
    //sets text to display and parent of text
    textToDisplay.setPlainText(text);
    textToDisplay.setParentItem(this);
}

void MyButton::setTextOfButtonPosition()
{
    //sets position of text in the centre of button
    auto x = this->boundingRect().width()/2 - textToDisplay.boundingRect().width()/2;
    auto y = this->boundingRect().height()/2 - textToDisplay.boundingRect().height()/2;
    textToDisplay.setPos(x,y);
}

void MyButton::quit()
{
    //slot quit, for button QUIT-> leaves programm
}
