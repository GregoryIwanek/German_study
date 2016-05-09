#include "guesssentencesectionui.h"
#include <QDebug>

GuessSentenceSectionUI::GuessSentenceSectionUI()
{

}

void GuessSentenceSectionUI::setSceneFromParent(CustomScene *myScene)
{
    scene = myScene;
}

void GuessSentenceSectionUI::buildUI()
{
    setMenu();
    setCollisionRects();
    setSentenceAreaCollisionRect();
}

void GuessSentenceSectionUI::setMenu()
{
    setBorderRect();
    setSentenceAreas();
    setUIComponents();
    setMyButtonsMap();
}

void GuessSentenceSectionUI::setUIComponents()
{
    setButtons();
    setUiTexts();
    setInputUIComponents();
}

void GuessSentenceSectionUI::setBorderRect()
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

void GuessSentenceSectionUI::setCollisionRects()
{
    QVector<QPointF> outerCollisionRect;
    outerCollisionRect << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,580))
                       << getClosestGridPoint(QPointF(1160,580)) << getClosestGridPoint(QPointF(1160,40))
                       << getClosestGridPoint(QPointF(40,40));
    drawCollisionRect(outerCollisionRect);

    QVector<QPointF> endCollisionRect;
    endCollisionRect << getClosestGridPoint(QPointF(0,0)) << getClosestGridPoint(QPointF(0,620))
                       << getClosestGridPoint(QPointF(1200,620)) << getClosestGridPoint(QPointF(1200,0))
                       << getClosestGridPoint(QPointF(0,0));
    drawCollisionRect(endCollisionRect);
}

void GuessSentenceSectionUI::setSentenceAreaCollisionRect()
{
    QVector<QPointF> innerCollisionLeftLine;
    innerCollisionLeftLine << getClosestGridPoint(QPointF(sentenceAreaList.first()->getSentenceAreaCorners("leftTop")))
                           << getClosestGridPoint(QPointF(sentenceAreaList.last()->getSentenceAreaCorners("leftBottom")));
    drawCollisionRect(innerCollisionLeftLine);

    QVector<QPointF> innerCollisionRightLine;
    innerCollisionRightLine << getClosestGridPoint(QPointF(sentenceAreaList.last()->getSentenceAreaCorners("rightBottom")))
                            << getClosestGridPoint(QPointF(sentenceAreaList.first()->getSentenceAreaCorners("rightTop")));
    drawCollisionRect(innerCollisionRightLine);
}

void GuessSentenceSectionUI::drawCollisionRect(QVector<QPointF> listOfPoints)
{
    for (auto i=0, n=listOfPoints.size()-1; i<n; ++i){
        QPointF start(listOfPoints[i]);
        QPointF end(listOfPoints[i+1]);
        QGraphicsLineItem *line = new QGraphicsLineItem(start.x(),start.y(),end.x(),end.y());
        line->setPen(apperiance->blackPen);
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
        sentenceArea->getPositionFromSceneToVariable(sentenceArea->pos());
        sentenceArea->setCornersToMap();
        sentenceAreaList.append(sentenceArea);
    }
}

void GuessSentenceSectionUI::setButtons()
{
    buttonBack = new MyButton();
    buttonBack->setGeometryOfButton(75,500,125,60);
    buttonBack->defineTextOfButton(QString("BACK"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonBack);

    buttonClear = new MyButton();
    buttonClear->setGeometryOfButton(250,500,125,60);
    buttonClear->defineTextOfButton(QString("RESET"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonClear);

    buttonCheck = new MyButton();
    buttonCheck->setGeometryOfButton(425,500,125,60);
    buttonCheck->defineTextOfButton(QString("CHECK"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonCheck);

    buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,500,125,60);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    scene->addItem(buttonStart);

    buttonHint = new MyButton();
    buttonHint->setGeometryOfButton(1000,430,100,40);
    buttonHint->defineTextOfButton(QString("HINT"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonHint->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonHint);
}

void GuessSentenceSectionUI::setUiTexts()
{
    points = new QGraphicsTextItem();
    points->setPos(100,340);
    points->setFont(apperiance->fontComicSans);
    points->setPlainText(QString("SCORE: 0"));
    scene->addItem(points);

    translation = new QGraphicsTextItem();
    translation->setPos(100,380);
    translation->setFont(apperiance->fontComicSans);
    translation->setPlainText(QString("WELCOME"));
    scene->addItem(translation);

    result = new QGraphicsTextItem();
    result->setPos(300,340);
    result->setFont(apperiance->fontComicSans);
    result->setPlainText(" ");
    scene->addItem(result);
}

void GuessSentenceSectionUI::setInputUIComponents()
{
    lineEdit = new QLineEdit();
    lineEdit->setFixedSize(800,50);
    lineEdit->setFont(apperiance->fontComicSans_15);
    lineEdit->move(100,430);
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
        lineEdit->clear();
    }
    else {
        result->setPlainText(" ");
        translation->setPlainText(" ");
        lineEdit->clear();
    }
}

void GuessSentenceSectionUI::sendLineEditData()
{
    emit signalSendLineEditData(lineEdit->text());
}
