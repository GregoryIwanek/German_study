#include "wordcontainer.h"
#include "apperiance.h"
#include "customscene.h"
#include <QDebug>
#include <QBrush>
#include <QApplication>
#include <qmath.h>
extern Apperiance *apperiance;

WordContainer::WordContainer(Word *myWord)
{
    //setMyFlags();
    setText(myWord);
    setSizeOfRect();
    setColor(apperiance->brushDarkGray);
    setTextPosition();

    setTimersAndConnections();

    //setStartPosition(point); called from mainWindow.cpp
}

void WordContainer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (isMoved == false){
         setDistanceAndDirectionToMoveToArea();
    }
    else setDistanceAndDirectionToMoveFromArea();

    emit clicked(this);

    if (timer->isActive() == false){
        timer->start(10);
    }
    else {
        timer->stop();
    }
}

void WordContainer::setTimersAndConnections()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void WordContainer::setMyFlags()
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

void WordContainer::setColor(QBrush brush)
{
    setBrush(brush);
    setOpacity(0.85);
}

void WordContainer::setText(Word *myWord)
{
    text = myWord;
}

void WordContainer::setTextPosition()
{
    int x = this->boundingRect().width()/2 - widthOfText/2;
    int y = this->boundingRect().height()/2 - heightOfText/2;
    text->setParentItem(this);
}

void WordContainer::setSizeOfRect()
{
    int gridSize = 20;
    widthOfText = text->getWidthOfText();
    heightOfText = text->getHeightOfText();
    widthOfRect = round(((widthOfText/gridSize)+1))*gridSize;
    heightOfRect = round(heightOfText/gridSize)*gridSize;
    setRect(0,0,widthOfRect,40);
}

void WordContainer::setStartPosition(QPointF point)
{
    startPosition = point;
}

void WordContainer::setIsMoved(bool isChecked)
{
    isMoved = isChecked;
}

int WordContainer::getHeightOfRect()
{
    return heightOfRect;
}

QPointF WordContainer::getStartPosition()
{
    return startPosition;
}

bool WordContainer::getIsMoved(){
    return isMoved;
}

void WordContainer::sendToStartArea(QPointF point)
{
    setPos(startPosition);
    setIsMoved(false);
}

QVariant WordContainer::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                qobject_cast<CustomScene*> (scene())){
            CustomScene* customScene = qobject_cast<CustomScene*> (scene());
            int gridSize = customScene->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}

void WordContainer::setPos(const QPointF &pos)
{
    //override default setPos function to move by only on grid nodes
    int gridSize = 20;
    qreal xV = round(pos.x()/gridSize)*gridSize;
    qreal yV = round(pos.y()/gridSize)*gridSize;

    QGraphicsItem::setPos(xV,yV);
}

void WordContainer::setNextContainerPositionInSentenceArea(QPointF *point)
{
    nextContainerPositionInSentenceArea = point;
}

void WordContainer::sendToSentenceArea(QPointF point)
{
    int stepSize = 10;
    double alpha = rotation(); //converting to degrees, angle has to be a double
    double dy = stepSize * qSin(qDegreesToRadians(alpha));
    double dx = stepSize * qCos(qDegreesToRadians(alpha));
    setPos(QPointF(this->x()+dx,this->y()+dy));
    setIsMoved(true);
}

void WordContainer::move()
{
    int stepSize = 10;
    double alpha = angleToMove;//rotation(); //converting to degrees, angle has to be a double
    double dy = stepSize * qSin(qDegreesToRadians(alpha));
    double dx = stepSize * qCos(qDegreesToRadians(alpha));
    QGraphicsItem::setPos(this->x()+dx,this->y()+dy);
//    setIsMoved(true);
    checkIfStopMovement();
}

void WordContainer::checkIfStopMovement()
{
    if (this->isMoved == true && this->y() <= nextContainerPositionInSentenceArea->y()){
        timer->stop();
        qDebug()<<isMoved;
        this->setPos(QPointF(nextContainerPositionInSentenceArea->x(), nextContainerPositionInSentenceArea->y()));
        emit stopped(this,true);
    }
    else if (this->isMoved == false && this->y() >= startPosition.y()){
        timer->stop();
        qDebug()<<isMoved;
        qDebug()<<2;
        this->setPos(QPointF(startPosition.x(), startPosition.y()));
        emit stopped(this,false);
    }
}

void WordContainer::setDistanceAndDirectionToMoveToArea()
{
    QLineF line;
    line.setLine(this->x(),this->y(),nextContainerPositionInSentenceArea->x(), nextContainerPositionInSentenceArea->y());
    angleToMove = -1* line.angle();
    qDebug()<<line;
}

void WordContainer::setDistanceAndDirectionToMoveFromArea()
{
    QLineF line;
    line.setLine(this->x(),this->y(),startPosition.x(), startPosition.y());
    angleToMove = -1* line.angle();
    qDebug()<<line;
}

int WordContainer::getWidthOfRect()
{
    return widthOfRect;
}
