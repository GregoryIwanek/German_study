#include "flashcardssectionui.h"
#include <QVector>
#include "wordcontainer.h"
#include "word.h"
#include <QDebug>
#include "apperiance.h"

extern Apperiance *apperiance;

FlashCardSectionUI::FlashCardSectionUI()
{

}

void FlashCardSectionUI::setSceneFromParent(CustomScene *myScene)
{
    //sets main window scene as a scene to draw on
    scene = myScene;
}

void FlashCardSectionUI::buildUI()
{
    //sets interface
    setMenu();
}

void FlashCardSectionUI::setMenu()
{
    //builds interface and defines basic information for use ( map of buttons)
    setBorderRect();
    setUIComponents();
    setMyButtonsMap();
}

void FlashCardSectionUI::setUIComponents()
{
    //sets UI components like buttons and texts
    setButtons();
    //setUiTexts();->TODO later, sets timer and counts time of guessing
}

void FlashCardSectionUI::setButtons()
{
    //defines all buttons and their geometry, text, size etc., adds to scene
    buttonBack = new MyButton();
    buttonBack->setGeometryOfButton(75,500,125,60);
    buttonBack->defineTextOfButton(QString("BACK"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonBack->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonBack);

    buttonClear = new MyButton();
    buttonClear->setGeometryOfButton(250,500,125,60);
    buttonClear->defineTextOfButton(QString("RESET"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonClear->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonClear);

    buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,500,125,60);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonStart->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonStart);
}

void FlashCardSectionUI::setUiTexts()
{
    //defines text with time
    time = new QGraphicsTextItem();
    time->setPos(450,500);
    time->setFont(apperiance->fontComicSans);
    time->setPlainText(QString("0:00.00"));
    scene->addItem(time);
}

void FlashCardSectionUI::setBorderRect()
{
    //sets inner and outer border rectangle around window
    //store corners points coordinates in vector
    QVector<QPointF> borderPointsOuter;
    borderPointsOuter << getClosestGridPoint(QPointF(20,20)) << getClosestGridPoint(QPointF(20,600))
                      << getClosestGridPoint(QPointF(1180,600)) << getClosestGridPoint(QPointF(1180,20));
    QVector<QPointF> borderPointsInner;
    borderPointsInner << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,580))
                      << getClosestGridPoint(QPointF(1160,580)) << getClosestGridPoint(QPointF(1160,40));

    //draws rectangle polygon by using corner points
    QPolygonF borderRectangleOuter(borderPointsOuter);
    this->scene->addPolygon(borderRectangleOuter);
    QPolygonF borderRectangleInner(borderPointsInner);
    this->scene->addPolygon(borderRectangleInner);
}

void FlashCardSectionUI::setMyButtonsMap()
{
    //sets button map for calling buttons in connections
    myButtonsMap["buttonBack"] = buttonBack;
    myButtonsMap["buttonClear"] = buttonClear;
    myButtonsMap["buttonStart"] = buttonStart;
}

//GETTERS

QPointF FlashCardSectionUI::getClosestGridPoint(QPointF point)
{
    return scene->getGridPoint(point);
}

MyButton *FlashCardSectionUI::getMyButton(QString nameOfButton)
{
    return myButtonsMap[nameOfButton];
}

void FlashCardSectionUI::back()
{
    //signal to back to main menu
    emit signalBack(this->parent());
}
