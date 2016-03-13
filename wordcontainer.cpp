#include "wordcontainer.h"
#include "apperiance.h"
#include <QDebug>
#include <QBrush>

extern Apperiance *apperiance;

WordContainer::WordContainer(){
    setText();
    setSizeOfRect();
    setSize(getWidthOfRect()*1.1, 45);
    setColor(apperiance->brushGreen);
    setTextPosition();
    //setStartPosition(point); called from mainWindow.cpp
    //setFlag(QGraphicsItem::ItemIsMovable);
}

void WordContainer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked(this);
}

void WordContainer::setSize(int width, int height){
    setRect(0,0,width,height);
}

void WordContainer::setColor(QBrush brush){
    setBrush(brush);
    setOpacity(0.85);
}

void WordContainer::setText(){
    text.defineInstance(this, QString("OOOOO"), apperiance->fontComicSans);
}

void WordContainer::setTextPosition(){
    int x = this->boundingRect().width()/2 - widthOfRect/2;
    int y = this->boundingRect().height()/2 - heightOfRect/2;
    text.setPos(x,y);
}

void WordContainer::setSizeOfRect(){
    widthOfRect = text.getWidthOfText();
    heightOfRect = text.getHeightOfText();
}

void WordContainer::setStartPosition(QPointF point){
    startPosition = point;
}

void WordContainer::setIsMoved(bool isChecked){
    isMoved = isChecked;
}

double WordContainer::getHeightOfRect(){
    return heightOfRect;
}

QPointF WordContainer::getStartPosition(){
    return startPosition;
}

bool WordContainer::getIsMoved(){
    return isMoved;
}

void WordContainer::sendToStartArea(QPointF point){
    setPos(startPosition);
    setIsMoved(false);
}

void WordContainer::sendToSentenceArea(QPointF point){
    setPos(point);
    setIsMoved(true);
}

double WordContainer::getWidthOfRect(){
    return widthOfRect;
}
