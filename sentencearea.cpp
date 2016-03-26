#include "sentencearea.h"
#include "apperiance.h"

extern Apperiance *apperiance;

SentenceArea::SentenceArea(){
    setSizeOfArea();
    setSizeOfLines();
    setLinesPosition();
    setBrushes();
    setZValue(-1);
}

void SentenceArea::setSizeOfArea(){
    setRect(0,0,1080,80);
}

void SentenceArea::setSizeOfLines(){
    lineWidth = boundingRect().width();
    lineHeight = 2;
}

void SentenceArea::setLinesPosition(){
    lineTop.setRect(0,0,lineWidth,lineHeight);
    lineBottom.setRect(0,boundingRect().height()-lineHeight,lineWidth,lineHeight);
    lineTop.setParentItem(this);
    lineBottom.setParentItem(this);
}

void SentenceArea::setBrushes(){
    setBrush(apperiance->brushGreen);
    lineTop.setBrush(apperiance->brushBlack);
    lineBottom.setBrush(apperiance->brushBlack);
}

void SentenceArea::setSpaceLeft(){

}

void SentenceArea::setWordContainerStartPosition(QPointF position){
    wordContainerStartPosition.setY(position.y()+20);
    wordContainerStartPosition.setX(position.x());
}

int SentenceArea::getSpaceLeft(){
    return spaceLeft;
}

QPointF SentenceArea::getWordContainerStartPosition(){
    return wordContainerStartPosition;
}

