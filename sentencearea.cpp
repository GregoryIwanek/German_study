#include "sentencearea.h"
#include "apperiance.h"
#include <QDebug>
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
    width = boundingRect().width();
    height = boundingRect().height();
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
    setBrush(apperiance->brushBlack);
    lineTop.setBrush(apperiance->brushBlack);
    lineBottom.setBrush(apperiance->brushBlack);
    setOpacity(0.5);
}

void SentenceArea::setSpaceLeft(){

}

void SentenceArea::setWordContainerStartPosition(QPointF position){
    wordContainerStartPosition.setY(position.y()+20);
    wordContainerStartPosition.setX(position.x());
}

void SentenceArea::getPositionFromSceneToVariable(QPointF position)
{
    positionOnScene = position;
}

void SentenceArea::setCornersToMap()
{
    sentenceAreaCorners["leftTop"] = positionOnScene;
    sentenceAreaCorners["leftBottom"] = QPointF(positionOnScene.x(), positionOnScene.y() + height);
    sentenceAreaCorners["rightBottom"] = QPointF(positionOnScene.x() + width, positionOnScene.y() + height);
    sentenceAreaCorners["rightTop"] = QPointF(positionOnScene.x() + width, positionOnScene.y());
}

int SentenceArea::getSpaceLeft(){
    return spaceLeft;
}

QPointF SentenceArea::getWordContainerStartPosition(){
    return wordContainerStartPosition;
}

double SentenceArea::getWidth()
{
    return width;
}

double SentenceArea::getHeight()
{
    return height;
}

QPointF SentenceArea::getSentenceAreaCorners(QString nameOfCorner)
{
    return sentenceAreaCorners[nameOfCorner];
}

