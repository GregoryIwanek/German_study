#include "guesssentencesection.h"
#include "mainwindow.h"
#include "wordcontainer.h"
#include "sentencearea.h"
#include "apperiance.h"
#include <QDebug>
#include <QVector>
#include <QGraphicsPolygonItem>
#include <QLineEdit>
#include <QTextEdit>
#include <QGraphicsWidget>
#include "test.h"
#include "customscene.h"
#include "QTime"
#include <stdlib.h>
#include <qmath.h>
#include "sentence.h"
#include "mybutton.h"
extern Apperiance *apperiance;
GuessSentenceSection::GuessSentenceSection()
{
    systemTime = new QTime();
    srand(time_t(systemTime));
}

void GuessSentenceSection::setSceneFromMainWindow(CustomScene *myScene)
{
    this->scene = myScene;
}

void GuessSentenceSection::setKeyEventFromMainWindow(QKeyEvent *event)
{

}

void GuessSentenceSection::setMenu()
{
    setBorderRect();
    setSentenceAreas();
    setUIComponents();
    setConnections();
}

void GuessSentenceSection::setUIComponents()
{
    setButtons();
    setUiTexts();
    setInputUIComponents();
}

void GuessSentenceSection::setButtons()
{
    MyButton *buttonBack = new MyButton();
    buttonBack->setGeometryOfButton(75,475,150,75);
    buttonBack->defineTextOfButton(QString("BACK"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonBack,SIGNAL(clicked()),this,SLOT(back()));
    scene->addItem(buttonBack);

    MyButton *buttonReset = new MyButton();
    buttonReset->setGeometryOfButton(250,475,150,75);
    buttonReset->defineTextOfButton(QString("RESET"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonReset,SIGNAL(clicked()),this,SLOT(clearSentence()));
    scene->addItem(buttonReset);

    MyButton *buttonCheck = new MyButton();
    buttonCheck->setGeometryOfButton(425,475,150,75);
    buttonCheck->defineTextOfButton(QString("CHECK"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonCheck,SIGNAL(clicked()),this,SLOT(checkIfSentenceCorrect()));
    scene->addItem(buttonCheck);

    MyButton *buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,475,150,75);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonStart,SIGNAL(clicked()),this,SLOT(setNewSentence()));
    scene->addItem(buttonStart);
}

void GuessSentenceSection::setUiTexts()
{
    points = new QGraphicsTextItem();
    points->setPos(100,300);
    points->setFont(apperiance->fontComicSans);
    points->setPlainText(QString("SCORE: ")+QString::number(pointsOfPlayer));
    scene->addItem(points);

    translation = new QGraphicsTextItem();
    translation->setPos(100,350);
    translation->setFont(apperiance->fontComicSans);
    translation->setPlainText(QString("WELCOME"));
    scene->addItem(translation);

    result = new QGraphicsTextItem();
    result->setPos(300,300);
    result->setFont(apperiance->fontComicSans);
    result->setPlainText(" ");
    scene->addItem(result);
}

void GuessSentenceSection::setInputUIComponents(){
    lineEdit = new QLineEdit();
    lineEdit->setFixedSize(800,50);
    lineEdit->setFont(apperiance->fontComicSans_15);
    lineEdit->move(100,400);
    scene->addWidget(lineEdit);
}

void GuessSentenceSection::checkIfSentenceInputInQLineEditIsCorrect()
{

    if (QString::compare(lineEdit->text(),sentence,Qt::CaseInsensitive)){
        updatePoints(true);
    }
    else {
        updatePoints(false);
    }
}

void GuessSentenceSection::setConnections()
{
    connect(this,SIGNAL(pointsChanged()),this,SLOT(updatePointsText()));
    connect(this,SIGNAL(sentenceChanged()),this,SLOT(updateSentenceText()));
    connect(this,SIGNAL(resultChanged(bool)),this,SLOT(updateResultText(bool)));
    connect(this,SIGNAL(keyStartPressed()),this,SLOT(setNewSentence()));
    connect(this,SIGNAL(keyCheckPressed()),this,SLOT(checkIfSentenceCorrect()));
    connect(this,SIGNAL(keyClearPressed()),this,SLOT(clearSentence()));
    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(checkIfSentenceInputInQLineEditIsCorrect()));
}

void GuessSentenceSection::setBorderRect()
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

void GuessSentenceSection::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space){
        emit keyStartPressed();
    }
    else if (event->key() == Qt::Key_Return && sentenceList.isEmpty() == false && sentenceList.last()->getIfSentenceChecked() == false){
        emit keyCheckPressed();
    }
    else if (event->key() == Qt::Key_Return && sentenceList.isEmpty() == false){
        emit keyClearPressed();
    }
}

void GuessSentenceSection::setWordContainers(Sentence *sentence)
{
    setColumn(sentence);
}

void GuessSentenceSection::setColumn(Sentence *sentence)
{
    for (int y=0, n=1; y<n; ++y){
        setRow(y, sentence);
    }
}

void GuessSentenceSection::setRow(int y, Sentence *sentence)
{
    for (int x=0, n=sentence->sentenceData.getListOfWordsInRandomOrder().size(); x<n; ++x){
        WordContainer *wordContainer = new WordContainer(sentence->sentenceData.getListOfWordsInRandomOrder()[x]);
        wordContainer->setPos(QPointF(60+endOfWordContainer, 240 + y*(wordContainer->boundingRect().height()+20)));
        endOfWordContainer += wordContainer->boundingRect().width() +20;
        wordContainer->setStartPosition(wordContainer->pos());
        //checkWordContainerCollision(wordContainer->getStartPosition());
        this->scene->addItem(wordContainer);
        wordContainerList.append(wordContainer);
        connect(wordContainer,SIGNAL(stopped(WordContainer*,bool)),this,SLOT(setNextWordContainerPosition(WordContainer*,bool)));
        connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
        //connect(wordContainer,SIGNAL(removeGapInSpace(WordContainer*)),this,SLOT(removeGapFromSentenceArea(WordContainer*)));
        //connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(updateSentence(WordContainer*)));
    }
    endOfWordContainer = 0;
}

void GuessSentenceSection::setSentenceAreas(){
    //create areas to put rects with words in
    for (int i=0, n=2; i<n; ++i){
        SentenceArea *sentenceArea = new SentenceArea();
        sentenceArea->setPos(60,60+i*sentenceArea->boundingRect().height());
        this->scene->addItem(sentenceArea);
        sentenceArea->setWordContainerStartPosition(sentenceArea->pos());
        sentenceAreaList.append(sentenceArea);
    }
}

void GuessSentenceSection::setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved)
{
    if (isWordContainerMoved == true){
        nextWordContainerPosition.setX(nextWordContainerPosition.x() + wordContainer->boundingRect().width()+19);
        nextWordContainerPosition.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
        nextWordContainerPositionPointer = &nextWordContainerPosition;
    }
    else {
        nextWordContainerPosition.setX(nextWordContainerPosition.x() - wordContainer->getWidthOfRect()-19);
        nextWordContainerPosition.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
        nextWordContainerPositionPointer = &nextWordContainerPosition;
    }
}

void GuessSentenceSection::updateSentence(WordContainer *wordContainer)
{
    if (wordContainer->getIsOnSentenceArea() == true){
        sentenceInputByUserList.append(wordContainer->getTextFromWord());
    }
    else {
        sentenceInputByUserList.removeAt(wordContainer->getIndexOnSentenceArea());
        //updateIndexOfWordContainersOnSentenceArea(wordContainer->getIndexOnSentenceArea());
        wordContainer->setIndexOnSentenceArea(NULL);
    }
}

void GuessSentenceSection::setSignNextWordContainerPositionToContainers()
{
    for (size_t i=0, n=wordContainerList.size(); i<n; i++){
        wordContainerList[i]->setNextContainerPositionInSentenceArea(nextWordContainerPositionPointer);
    }
}

void GuessSentenceSection::setVariables()
{
    nextWordContainerPosition = QPointF(sentenceAreaList.first()->getWordContainerStartPosition().x()+20,
                                        sentenceAreaList.first()->getWordContainerStartPosition().y());
    nextWordContainerPositionPointer = &nextWordContainerPosition;
}

void GuessSentenceSection::checkWordContainerCollision(QPointF startPointOfChecked)
{
    QPointF startingPoint = startPointOfChecked;
    for (int i=0, n=wordContainerList.size(); i<n; ++i){
        if (typeid(*(wordContainerList[i])) == typeid(WordContainer))
        {
            wordContainerList[i]->setPos(QPointF(startingPoint.x()+20,startingPoint.y()+20));
        }
    }
}

void GuessSentenceSection::setIndexOfWordContainerOnSentenceArea(WordContainer *wordContainer)
{
    if (wordContainer->getIsOnSentenceArea() == true){
        --indexOfWordContainerOnSentenceArea;
        removeGapFromSentenceArea(wordContainer);
        updateIndexOfWordContainersOnSentenceArea(wordContainer->getIndexOnSentenceArea());
    }
    else {
        wordContainer->setIndexOnSentenceArea(indexOfWordContainerOnSentenceArea);
        ++indexOfWordContainerOnSentenceArea;
    }
}

void GuessSentenceSection::updateIndexOfWordContainersOnSentenceArea(int index)
{
    for (size_t i=0, n=wordContainerList.size(); i<n; ++i){
        if (wordContainerList[i]->getIsOnSentenceArea() == true && wordContainerList[i]->getIndexOnSentenceArea() > index){
            wordContainerList[i]->setIndexOnSentenceArea(wordContainerList[i]->getIndexOnSentenceArea()-1);
        }
    }
}

void GuessSentenceSection::updateIndexOfSentenceInputByUserList(WordContainer *wordContainer)
{
    for (size_t i=wordContainer->getIndexOnSentenceArea(), n=sentenceInputByUserList.size(); i<n; i++){
        if (i<n-1){
            sentenceInputByUserList[i] = sentenceInputByUserList[i+1];
        }
        else sentenceInputByUserList.removeLast();
    }
}


QPointF GuessSentenceSection::getClosestGridPoint(QPointF point)
{
    return scene->getGridPoint(point);
}

void GuessSentenceSection::sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer)
{
    if (wordContainer->getIsOnSentenceArea()==false) {
        setIndexOfWordContainerOnSentenceArea(wordContainer);
        wordContainer->setIsOnSentenceArea(true);
        updateSentence(wordContainer);
    }
    else {
        setIndexOfWordContainerOnSentenceArea(wordContainer);
        wordContainer->setIsOnSentenceArea(false);
        updateSentence(wordContainer);
    }
}


void GuessSentenceSection::setGuessSentenceSectionVisible()
{
    this->scene->clear();
    setMenu();
}

void GuessSentenceSection::setNewSentence()
{
    if (sentenceList.isEmpty()){
        Sentence *sentence = new Sentence();
        sentenceList.append(sentence);
        setVariables();
        setWordContainers(sentence);
        setSignNextWordContainerPositionToContainers();
        emit sentenceChanged();
    }
}

void GuessSentenceSection::checkIfSentenceCorrect()
{
    if (sentenceList.isEmpty() == false){

        if (sentenceList.last()->sentenceData.getCorrectSentence() == sentenceInputByUserList &&
                sentenceList.last()->getIfSentenceChecked() == false){

            updatePoints(true);
            sentenceList.last()->setSentenceChecked(true);
        }
        else if (sentenceList.last()->getIfSentenceChecked() == false){
            updatePoints(false);
        }
    }
}

void GuessSentenceSection::updatePoints(bool increased)
{
    if (increased == true){
        ++pointsOfPlayer;
        updateColorOfCorrectWordContainers();
        emit resultChanged(true);
    }
    else if(increased == false && pointsOfPlayer > 0){
        --pointsOfPlayer;
        emit resultChanged(false);
    }
    else emit resultChanged(false);

    emit pointsChanged();
}

void GuessSentenceSection::updateColorOfCorrectWordContainers()
{
    for (size_t i=0, n=wordContainerList.size(); i<n; ++i){

        if (wordContainerList[i]->getIsOnSentenceArea() == true){
            wordContainerList[i]->setBrush(apperiance->brushGreen);
        }
    }
}

void GuessSentenceSection::updateSentenceText()
{
    sentence.append(sentenceList.last()->sentenceData.getCorrectSentenceString());
    translation->setPlainText(sentenceList.last()->sentenceData.getCorrectTranslationString());
}

void GuessSentenceSection::updatePointsText()
{
    if (pointsOfPlayer >= 0){
        points->setPlainText(QString("SCORE: ")+QString::number(pointsOfPlayer));
    }
}

void GuessSentenceSection::updateResultText(bool isCorrect)
{
    if (isCorrect == true){
        result->setPlainText(QString("CORRECT! YOU GET A POINT!"));
        result->setDefaultTextColor(Qt::green);
    }
    else {
        result->setPlainText(QString("WRONG! YOU LOSE A POINT!"));
        result->setDefaultTextColor(Qt::blue);
    }
}

void GuessSentenceSection::removeGapFromSentenceArea(WordContainer *wordContainer)
{
    for (size_t i=0, n=wordContainerList.size(); i<n; ++i){

        if (wordContainerList[i]->getIndexOnSentenceArea() != NULL &&
                wordContainerList[i]->getIndexOnSentenceArea() > wordContainer->getIndexOnSentenceArea()){

            wordContainerList[i]->setPos(QPointF(wordContainerList[i]->pos().x()-(wordContainer->getWidthOfRect()+20),
                                                 wordContainerList[i]->pos().y()));
        }
    }
}

void GuessSentenceSection::back()
{
    scene->clear();
}

void GuessSentenceSection::clearSentence()
{
    for(size_t i=0, n=wordContainerList.size(); i<n; i++){
        scene->removeItem(wordContainerList[i]);
        wordContainerList[i]->disconnect(wordContainerList[i],SIGNAL(clicked(WordContainer*)),
                                         this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
        delete wordContainerList[i];
    }
    wordContainerList.clear();
    sentenceInputByUserList.clear();
    sentenceList.clear();
    sentence.clear();
    result->setPlainText(QString(" "));
    indexOfWordContainerOnSentenceArea = 0;
}




