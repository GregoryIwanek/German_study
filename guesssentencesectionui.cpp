#include "guesssentencesectionui.h"
#include <QDebug>
GuessSentenceSectionUI::GuessSentenceSectionUI()
{

}

void GuessSentenceSectionUI::setSceneFromParent(CustomScene *myScene)
{
    scene = myScene;
}

void GuessSentenceSectionUI::setMenu()
{
    setBorderRect();
    setCollisionRect();
    setSentenceAreas();
    setUIComponents();
    setMyButtonsMap();
}

void GuessSentenceSectionUI::buildUI()
{
    setMenu();
}

void GuessSentenceSectionUI::setBorderRect()
{
    QVector<QPointF> borderPointsOuter;
    borderPointsOuter << getClosestGridPoint(QPointF(20,20)) << getClosestGridPoint(QPointF(20,580))
                      << getClosestGridPoint(QPointF(1180,580)) << getClosestGridPoint(QPointF(1180,20));
    QVector<QPointF> borderPointsInner;
    borderPointsInner << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,560))
                      << getClosestGridPoint(QPointF(1160,560)) << getClosestGridPoint(QPointF(1160,40));

    QPolygonF borderRectangleOuter(borderPointsOuter);
    this->scene->addPolygon(borderRectangleOuter);
    QPolygonF borderRectangleInner(borderPointsInner);
    this->scene->addPolygon(borderRectangleInner);
}

void GuessSentenceSectionUI::setCollisionRect()
{
    QVector<QPointF> borderPointsCollisionRect;
    borderPointsCollisionRect << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,560))
                              << getClosestGridPoint(QPointF(1160,560)) << getClosestGridPoint(QPointF(1160,40))
                              << getClosestGridPoint(QPointF(40,40));

                                 for (size_t i=0, n=borderPointsCollisionRect.size()-1; i<n; ++i){
        QPointF start(borderPointsCollisionRect[i]);
        QPointF end(borderPointsCollisionRect[i+1]);
        QGraphicsLineItem *line = new QGraphicsLineItem(start.x(),start.y(),end.x(),end.y());
        this->scene->addItem(line);
    }

}

void GuessSentenceSectionUI::setSentenceAreas()
{
    //create areas to put rects with words in
    for (int i=0, n=2; i<n; ++i){
        SentenceArea *sentenceArea = new SentenceArea();
        sentenceArea->setPos(60,60+i*sentenceArea->boundingRect().height());
        this->scene->addItem(sentenceArea);
        sentenceArea->setWordContainerStartPosition(sentenceArea->pos());
        sentenceAreaList.append(sentenceArea);
    }
}

void GuessSentenceSectionUI::setUIComponents()
{
    setButtons();
    setUiTexts();
    setInputUIComponents();
}

void GuessSentenceSectionUI::setButtons()
{
    buttonBack = new MyButton();
    buttonBack->setGeometryOfButton(75,480,125,60);
    buttonBack->defineTextOfButton(QString("BACK"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonBack);

    buttonClear = new MyButton();
    buttonClear->setGeometryOfButton(250,480,125,60);
    buttonClear->defineTextOfButton(QString("RESET"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonClear);

    buttonCheck = new MyButton();
    buttonCheck->setGeometryOfButton(425,480,125,60);
    buttonCheck->defineTextOfButton(QString("CHECK"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonCheck);

    buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,480,125,60);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonStart);
}

void GuessSentenceSectionUI::setUiTexts()
{
    points = new QGraphicsTextItem();
    points->setPos(100,320);
    points->setFont(apperiance->fontComicSans);
    points->setPlainText(QString("SCORE: 0"));
    scene->addItem(points);

    translation = new QGraphicsTextItem();
    translation->setPos(100,360);
    translation->setFont(apperiance->fontComicSans);
    translation->setPlainText(QString("WELCOME"));
    scene->addItem(translation);

    result = new QGraphicsTextItem();
    result->setPos(300,320);
    result->setFont(apperiance->fontComicSans);
    result->setPlainText(" ");
    scene->addItem(result);
}

void GuessSentenceSectionUI::setInputUIComponents()
{
    lineEdit = new QLineEdit();
    lineEdit->setFixedSize(800,50);
    lineEdit->setFont(apperiance->fontComicSans_15);
    lineEdit->move(100,420);
    scene->addWidget(lineEdit);
}

void GuessSentenceSectionUI::setMyButtonsMap()
{
    myButtonsMap["buttonBack"] = buttonBack;
    myButtonsMap["buttonClear"] = buttonClear;
    myButtonsMap["buttonCheck"] = buttonCheck;
    myButtonsMap["buttonStart"] = buttonStart;
}

QPointF GuessSentenceSectionUI::getClosestGridPoint(QPointF point)
{
    return scene->getGridPoint(point);
}

QList<SentenceArea *> GuessSentenceSectionUI::getSentenceAreaList()
{
    return sentenceAreaList;
}

MyButton *GuessSentenceSectionUI::getMyButton(QString nameOfButton)
{
    return myButtonsMap[nameOfButton];
}

QLineEdit *GuessSentenceSectionUI::getMyLineEdit()
{
    return lineEdit;
}

void GuessSentenceSectionUI::back()
{
    emit signalBack();
}

void GuessSentenceSectionUI::clearSentence()
{
    emit signalClearSentence();
}

void GuessSentenceSectionUI::checkIfSentenceCorrectButton()
{
    emit signalCheckIfSentenceIsCorrectButton();
}

void GuessSentenceSectionUI::setNewSentence()
{
    emit signalSetNewSentence();
}

void GuessSentenceSectionUI::updatePointsText(int number)
{
    if (number >= 0){
         points->setPlainText(QString("SCORE: ")+QString::number(number));
    }
}

void GuessSentenceSectionUI::updateSentenceText(QString text)
{
    translation->setPlainText(text);
}

void GuessSentenceSectionUI::updateResultText(bool isResultCorrect)
{
    if (isResultCorrect == true){
        result->setPlainText(QString("CORRECT! YOU GET A POINT!"));
        result->setDefaultTextColor(Qt::green);
    }
    else {
        result->setPlainText(QString("WRONG! YOU LOSE A POINT!"));
        result->setDefaultTextColor(Qt::blue);
    }
}

void GuessSentenceSectionUI::clearUIText(bool isCompleteClear)
{
    if (isCompleteClear == true){
        result->setPlainText(" ");
        translation->setPlainText(" ");
        points->setPlainText(" ");
    }
    else {
        result->setPlainText(" ");
        translation->setPlainText(" ");
    }
}

void GuessSentenceSectionUI::sendLineEditData()
{
    emit signalSendLineEditData(lineEdit->text());
}
