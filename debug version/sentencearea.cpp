#include "sentencearea.h"
#include "apperiance.h"
#include <QDebug>
extern Apperiance *apperiance;

SentenceArea::SentenceArea()
{
    //steps to define sentence area on scene
    setSizeOfArea();
    setSizeOfLines();
    setLinesPosition();
    setBrushes();
    setZValue(-1);
}

void SentenceArea::setSizeOfArea()
{
    //sets given size of SentenceArea
    setRect(0,0,1080,80);

    //update information about size
    width = boundingRect().width();
    height = boundingRect().height();
}

void SentenceArea::setSizeOfLines()
{
    //sets to draw in sentence area ( top/bottom bold line)
    lineWidth = boundingRect().width();
    lineHeight = 2;
}

void SentenceArea::setLinesPosition()
{
    //define posiition of lines
    lineTop.setRect(0,0,lineWidth,lineHeight);
    lineBottom.setRect(0,boundingRect().height()-lineHeight,lineWidth,lineHeight);

    //sets parent to this SentenceArea (needed to do that to display them)
    lineTop.setParentItem(this);
    lineBottom.setParentItem(this);
}

void SentenceArea::setBrushes()
{
    //sets brush to draw SentenceArea and lines
    setBrush(apperiance->brushBlack);
    lineTop.setBrush(apperiance->brushBlack);
    lineBottom.setBrush(apperiance->brushBlack);

    //sets semi transparency
    setOpacity(0.5);
}

void SentenceArea::setWordContainerStartPosition(QPointF position)
{
    //sets destination coordinates to first WordContainer send to this SentenceArea
    wordContainerStartPosition.setY(position.y()+20);
    wordContainerStartPosition.setX(position.x());
}

void SentenceArea::setPositionFromSceneToVariable(QPointF position)
{
    //sets information about position of SentenceArea inside of window of program ( called from GSSection UI)
    positionOnScene = position;
}

void SentenceArea::setCornersToMap()
{
    //sets map with coordinates of corners of the SentenceArea ( for use in GSSection to check if WC is out of SentenceArea)
    sentenceAreaCorners["leftTop"] = positionOnScene;
    sentenceAreaCorners["leftBottom"] = QPointF(positionOnScene.x(), positionOnScene.y() + height);
    sentenceAreaCorners["rightBottom"] = QPointF(positionOnScene.x() + width, positionOnScene.y() + height);
    sentenceAreaCorners["rightTop"] = QPointF(positionOnScene.x() + width, positionOnScene.y());
}

//GETTERS

QPointF SentenceArea::getWordContainerStartPosition()
{
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

