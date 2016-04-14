#include "wordcontainer.h"
#include "apperiance.h"
#include "customscene.h"
#include <QDebug>
#include <QBrush>
#include <QApplication>

extern Apperiance *apperiance;

WordContainer::WordContainer(Word *myWord)
{
    setMyFlags();
    setText(myWord);
    setSizeOfRect();
    setColor(apperiance->brushGreen);
    setTextPosition();
    //setStartPosition(point); called from mainWindow.cpp
}

//WordContainer::WordContainer(Word &word)
//{
//    setWord(word);
//    setMyFlags();
//    setText();
//    setSizeOfRect();
//    setColor(apperiance->brushGreen);
//    setTextPosition();
//}

void WordContainer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
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
    //word = *myWord;
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

void WordContainer::sendToSentenceArea(QPointF point)
{
    setPos(point);
    setIsMoved(true);
}

int WordContainer::getWidthOfRect()
{
    return widthOfRect;
}
