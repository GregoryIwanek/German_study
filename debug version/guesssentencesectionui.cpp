#include "guesssentencesectionui.h"
#include <QDebug>
#include "apperiance.h"

extern Apperiance *apperiance;

GuessSentenceSectionUI::GuessSentenceSectionUI()
{

}

void GuessSentenceSectionUI::setSceneFromParent(CustomScene *myScene)
{
    //sets main scene as a scene for this section
    scene = myScene;
}

void GuessSentenceSectionUI::buildUI()
{
    //steps to build UI
    setMenu();
    setCollisionRects();
    setSentenceAreaCollisionRect();
}

void GuessSentenceSectionUI::setMenu()
{
    //sets main components and data
    setBorderRect();
    setSentenceAreas();
    setUIComponents();
    setMyButtonsMap();
}

void GuessSentenceSectionUI::setUIComponents()
{
    //sets interface elements
    setButtons();
    setUiTexts();
    setInputUIComponents();
    setHintImage();
}

void GuessSentenceSectionUI::setBorderRect()
{
    //sets border rect ( outer and inner)-> line around a main window
    //store corners coordinates in a vector
    QVector<QPointF> borderPointsOuter;
    borderPointsOuter << getClosestGridPoint(QPointF(20,20)) << getClosestGridPoint(QPointF(20,600))
                      << getClosestGridPoint(QPointF(1180,600)) << getClosestGridPoint(QPointF(1180,20));
    QVector<QPointF> borderPointsInner;
    borderPointsInner << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,580))
                      << getClosestGridPoint(QPointF(1160,580)) << getClosestGridPoint(QPointF(1160,40));

    //create and add polygon line to the scene
    QPolygonF borderRectangleOuter(borderPointsOuter);
    this->scene->addPolygon(borderRectangleOuter);
    QPolygonF borderRectangleInner(borderPointsInner);
    this->scene->addPolygon(borderRectangleInner);
}

void GuessSentenceSectionUI::setCollisionRects()
{
    //sets collision rects (invisible)-> for GSSection, to check if WC after send to Sentence Area is inside area, not far away in screen
    //store corners coordinates in a vector
    QVector<QPointF> outerCollisionRect;
    outerCollisionRect << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,580))
                       << getClosestGridPoint(QPointF(1160,580)) << getClosestGridPoint(QPointF(1160,40))
                       << getClosestGridPoint(QPointF(40,40));
    //sends vector to draw rect
    drawCollisionRect(outerCollisionRect);

    QVector<QPointF> endCollisionRect;
    endCollisionRect << getClosestGridPoint(QPointF(0,0)) << getClosestGridPoint(QPointF(0,620))
                     << getClosestGridPoint(QPointF(1200,620)) << getClosestGridPoint(QPointF(1200,0))
                     << getClosestGridPoint(QPointF(0,0));
    drawCollisionRect(endCollisionRect);
}

void GuessSentenceSectionUI::setSentenceAreaCollisionRect()
{
    //sets collision rect around sentence area border (invisible)
    //store corners coordinates for Sentence Area
    QVector<QPointF> innerCollisionLeftLine;
    innerCollisionLeftLine << getClosestGridPoint(QPointF(sentenceAreaList.first()->getSentenceAreaCorners("leftTop")))
                           << getClosestGridPoint(QPointF(sentenceAreaList.last()->getSentenceAreaCorners("leftBottom")));
    //sends vector to draw rect
    drawCollisionRect(innerCollisionLeftLine);

    QVector<QPointF> innerCollisionRightLine;
    innerCollisionRightLine << getClosestGridPoint(QPointF(sentenceAreaList.last()->getSentenceAreaCorners("rightBottom")))
                            << getClosestGridPoint(QPointF(sentenceAreaList.first()->getSentenceAreaCorners("rightTop")));
    drawCollisionRect(innerCollisionRightLine);
}

void GuessSentenceSectionUI::drawCollisionRect(QVector<QPointF> listOfPoints)
{
    //draws invisible collision rect on scene
    for (auto i=0, n=listOfPoints.size()-1; i<n; ++i)
    {
        //sets starting and ending point of line
        QPointF start(listOfPoints[i]);
        QPointF end(listOfPoints[i+1]);

        //draw line and add to scene
        QGraphicsLineItem *line = new QGraphicsLineItem(start.x(),start.y(),end.x(),end.y());
        line->setPen(apperiance->blackPen);
        this->scene->addItem(line);
    }
}

void GuessSentenceSectionUI::setSentenceAreas()
{
    //create areas to put WordContainers in
    for (int i=0, n=2; i<n; ++i)
    {
        SentenceArea *sentenceArea = new SentenceArea();

        //sets position and adds to scene
        sentenceArea->setPos(60,60+i*sentenceArea->boundingRect().height());
        this->scene->addItem(sentenceArea);

        //defines information about sentence area
        sentenceArea->setWordContainerStartPosition(sentenceArea->pos());
        sentenceArea->setPositionFromSceneToVariable(sentenceArea->pos());
        sentenceArea->setCornersToMap();

        //add SA to list
        sentenceAreaList.append(sentenceArea);
    }
}

void GuessSentenceSectionUI::setButtons()
{
    //defines main navigation buttons of the GSSection, geometry, text, hover events, adds to scene
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

    buttonCheck = new MyButton();
    buttonCheck->setGeometryOfButton(425,500,125,60);
    buttonCheck->defineTextOfButton(QString("CHECK"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonCheck->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonCheck);

    buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,500,125,60);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonStart->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonStart);

    buttonHint = new MyButton();
    buttonHint->setGeometryOfButton(1000,500,100,60);
    buttonHint->defineTextOfButton(QString("HINT"), apperiance->brushYellow, apperiance->fontComicSans);
    buttonHint->setHoverEvents(apperiance->brushGreen, apperiance->brushYellow);
    scene->addItem(buttonHint);
}

void GuessSentenceSectionUI::setUiTexts()
{
    //defines main display texts inside GSSection, position, font, text to print and ads to scene
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
    //sets LineEdit to put answer for GSSection from keyboard, sets geometry, font, position and adds to scene
    lineEdit = new QLineEdit();
    lineEdit->setFixedSize(800,50);
    lineEdit->setFont(apperiance->fontComicSans_15);
    lineEdit->move(100,430);
    scene->addWidget(lineEdit);
}

void GuessSentenceSectionUI::setHintImage()
{
    //sets image with tips about case system in german, sets position, value Z so always on top and add to scene
    hintImage = new QGraphicsPixmapItem(apperiance->pixmapHintImage);
    hintImage->setPos(1100 - hintImage->boundingRect().width(), 500 - hintImage->boundingRect().height());
    hintImage->setZValue(1);
    hintImage->hide();
    scene->addItem(hintImage);
}

void GuessSentenceSectionUI::setMyButtonsMap()
{
    //sets map of buttons to navigato to them from GSSection
    myButtonsMap["buttonBack"] = buttonBack;
    myButtonsMap["buttonClear"] = buttonClear;
    myButtonsMap["buttonCheck"] = buttonCheck;
    myButtonsMap["buttonStart"] = buttonStart;
    myButtonsMap["buttonHint"] = buttonHint;
}

//GETTERS

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
    emit signalBack(this->parent());
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
    //update sentence text in english
    translation->setPlainText(text);
}

void GuessSentenceSectionUI::updateResultText(bool isResultCorrect)
{
    //displays text if we are correct or wrong after clicked on CHECK button
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
    //clear texts after click on RESET
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
    //sends text from LineEdit to check
    emit signalSendLineEditData(lineEdit->text());
}

void GuessSentenceSectionUI::showHideHint()
{
    //switch hint image on//off
    if (hintImage->isVisible() == true){
        hintImage->hide();
    }
    else hintImage->show();
}
