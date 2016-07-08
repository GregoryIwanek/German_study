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
    //constructor used in GSSection, steps to define WordContainer in GSSection; size undefined, depends on lenght of text
    setText(myWord);
    setSizeOfRect();
    setColor(apperiance->brushDarkGray);
    setTextPosition();

    setTimersAndConnections();
}

WordContainer::WordContainer(int width, int height, Word *myWord, bool isItTranslation)
{
    //constructor used in FCSection, steps to define WordContainer in FCSection; size defined;
    setIfIsTranslation(isItTranslation);
    setText(myWord);
    setFixedSizeOfRect(width, height);
    setColor(apperiance->brushDarkGray);
    setTextPosition();

    setTimersAndConnections();
}

void WordContainer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // mouse double click event, depend if it's inside GSSection or FCSection
    if (sectionItBelongsTo == "GSSection")
    {
        //in GSSection-> move WordContainer to/back from SentenceArea
        sendContainerFromOrToSentenceArea();
        switchTimers();
    }
    else if (sectionItBelongsTo == "FCSection")
    {
        //in FCSection-> emits information, that WordContainer was clicked and program will point it to compare with second WordContainer
        emit clicked(this);
    }
}

void WordContainer::setTimersAndConnections()
{
    //sets timer and connect it to slot which calculates movement of WordContainer in GSSection
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void WordContainer::setColor(QBrush brush)
{
    //sets color of WordContainer
    setBrush(brush);
    setOpacity(0.85);
}

void WordContainer::setIfIsTranslation(bool isItTranslation)
{
    /*only for FCSection-> some WordContainers holds origin words (german), some hold translation of these words->
     *  specify which case is THIS WordContainer*/
    isItDisplayingTranslation = isItTranslation;
}

void WordContainer::setText(Word *myWord)
{
    // sets text to display for GSSection or FCSection
    text = myWord;

    if (isItDisplayingTranslation == true)
    {
        text->setText(text->getText(true), true);
    }
    else text->setText(text->getText(false), false);

    //updates information about size of text
    widthOfText = text->getWidthOfText();
    heightOfText = text->getHeightOfText();
}

void WordContainer::setTextPosition()
{
    //positions text in the centre of WordContainer
    text->setParentItem(this);
    text->setPos(this->boundingRect().width()/2 - widthOfText/2, this->boundingRect().height()/2 - heightOfText/2);
}

void WordContainer::setSizeOfRect()
{
    /*sets size of rectangle, if was not defined or we change font, of WordContainer by size of grid (20 pixels-> customScene class
    round "width" up/+20, just to make sure that word will fit there by width*/
    int gridSize = 20;
    widthOfRect = round(((widthOfText/gridSize)+1))*gridSize;
    heightOfRect = round(heightOfText/gridSize)*gridSize;
    setRect(0,0,widthOfRect,40);
}

void WordContainer::setFixedSizeOfRect(int width, int height)
{
    //sets fixed size of rectangle of WordContainer, size given at the beggining
    setRect(0,0,width,height);
}

QVariant WordContainer::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //NOT USED ANYMORE, but i leave it just in case-> before, used to move WordContainer on the grid by jumping by 20 pixels, by dragging with mouse
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
    //override default setPos function to move only on grid nodes ( jump 20 pixels)
    int gridSize = 20;
    qreal xV = round(pos.x()/gridSize)*gridSize;
    qreal yV = round(pos.y()/gridSize)*gridSize;

    QGraphicsItem::setPos(xV,yV);
}

void WordContainer::setNextContainerPositionInSentenceArea(QPointF *point)
{
    nextContainerPositionInSentenceArea = point;
}

void WordContainer::setIndexOnSentenceArea(int index)
{
    indexOnSentenceArea = index;
}

void WordContainer::setIsChecked(bool isItemChecked)
{
    isChecked = isItemChecked;
}

void WordContainer::setSectionItBelongsTo(QString section)
{
    //sets section (GSSection/FCSection)
    sectionItBelongsTo = section;
}

void WordContainer::sendContainerFromOrToSentenceArea()
{
    //sets if we send WC from or to Sentence Area
    if (isOnSentenceArea == false){
        setDistanceAndDirectionToMoveToArea();
        emit clicked(this);
    }
    else {
        setDistanceAndDirectionToMoveFromArea();
        emit clicked(this);
    }
}

void WordContainer::switchTimers()
{
    //turn on/ turn off timer, depending on stage of clicked WC
    if (timer->isActive() == false){
        timer->start(10);
    }
    else {
        timer->stop();
    }
}

void WordContainer::move()
{
    //moves WC every tick of timer by defined step and calculated angle
    int stepSize = 15;
    double alpha = angleToMove;//rotation(); //converting to degrees, angle has to be a double
    double dy = stepSize * qSin(qDegreesToRadians(alpha));
    double dx = stepSize * qCos(qDegreesToRadians(alpha));
    QGraphicsItem::setPos(this->x()+dx,this->y()+dy);

    //check if stopp move of WC
    checkIfStopMovement();
}

void WordContainer::checkIfStopMovement()
{
    /*checks every ticks of Timer if we reached destination and should stop movement of WordContainer
    stops timer and sends signal that it stopped */
    if (this->isOnSentenceArea == true && this->y() <= nextContainerPositionInSentenceArea->y()){
        timer->stop();
        this->setPos(QPointF(nextContainerPositionInSentenceArea->x(), nextContainerPositionInSentenceArea->y()));
        emit stopped(this,true);
    }
    else if (this->isOnSentenceArea == false && this->y() >= startPosition.y()){
        timer->stop();
        this->setPos(QPointF(startPosition.x(), startPosition.y()));
        emit stopped(this,false);
    }
}

void WordContainer::setDistanceAndDirectionToMoveToArea()
{
    //sets line to move on, from starting position of WC to position on Sencence Area
    QLineF line;
    line.setLine(this->x(),this->y(),nextContainerPositionInSentenceArea->x(), nextContainerPositionInSentenceArea->y());
    angleToMove = -1* line.angle();
}

void WordContainer::setDistanceAndDirectionToMoveFromArea()
{
    //sets line to move on, from position on Sentence Area to the starting position of WC
    QLineF line;
    line.setLine(this->x(),this->y(),startPosition.x(), startPosition.y());
    angleToMove = -1* line.angle();
}

//GETTERS

void WordContainer::setStartPosition(QPointF point)
{
    startPosition = point;
}

void WordContainer::setIsOnSentenceArea(bool isChecked)
{
    isOnSentenceArea = isChecked;
}

double WordContainer::getWidthOfRect()
{
    return widthOfRect;
}

double WordContainer::getHeightOfRect()
{
    return heightOfRect;
}

QPointF WordContainer::getStartPosition()
{
    return startPosition;
}

QString WordContainer::getTextFromWord()
{
    return text->getText(false);
}

bool WordContainer::getIsOnSentenceArea(){
    return isOnSentenceArea;
}

bool WordContainer::getIfIsChecked()
{
    return isChecked;
}

int WordContainer::getIndexOnSentenceArea()
{
    return indexOnSentenceArea;
}

Word *WordContainer::getWordPointerOfWordContainer()
{
    return text;
}
