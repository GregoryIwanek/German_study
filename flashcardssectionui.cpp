#include "flashcardssectionui.h"
#include <QVector>
#include "wordcontainer.h"
#include "word.h"
#include <QDebug>
FlashCardSectionUI::FlashCardSectionUI()
{

}

void FlashCardSectionUI::setSceneFromParent(CustomScene *myScene)
{
    scene = myScene;
}

void FlashCardSectionUI::buildUI()
{
    setMenu();
}

void FlashCardSectionUI::setMenu()
{
    setBorderRect();
    setUIComponents();
    setMyButtonsMap();
}

void FlashCardSectionUI::setUIComponents()
{
    setButtons();
}

void FlashCardSectionUI::setButtons()
{
    buttonBack = new MyButton();
    buttonBack->setGeometryOfButton(75,500,125,60);
    buttonBack->defineTextOfButton(QString("BACK"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonBack);

    buttonClear = new MyButton();
    buttonClear->setGeometryOfButton(250,500,125,60);
    buttonClear->defineTextOfButton(QString("RESET"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonClear);

    buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,500,125,60);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonStart);
qDebug()<<1;
    for (int i=0, n=20; i<n; ++i){
        qDebug()<<2;
        Word *word = new Word();
        WordContainer *wc = new WordContainer(100,100,word);
        scene->addItem(wc);
        qDebug()<<2;
        wc->setPos(QPointF(600,400));
    }
}

void FlashCardSectionUI::setUiTexts()
{

}

void FlashCardSectionUI::setBorderRect()
{
    QVector<QPointF> borderPointsOuter;
    borderPointsOuter << getClosestGridPoint(QPointF(20,20)) << getClosestGridPoint(QPointF(20,600))
                      << getClosestGridPoint(QPointF(1180,600)) << getClosestGridPoint(QPointF(1180,20));
    QVector<QPointF> borderPointsInner;
    borderPointsInner << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,580))
                      << getClosestGridPoint(QPointF(1160,580)) << getClosestGridPoint(QPointF(1160,40));

    QPolygonF borderRectangleOuter(borderPointsOuter);
    this->scene->addPolygon(borderRectangleOuter);
    QPolygonF borderRectangleInner(borderPointsInner);
    this->scene->addPolygon(borderRectangleInner);
}

void FlashCardSectionUI::setMyButtonsMap()
{

}

QPointF FlashCardSectionUI::getClosestGridPoint(QPointF point)
{
    return scene->getGridPoint(point);
}
