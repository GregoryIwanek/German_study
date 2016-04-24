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

}

void GuessSentenceSection::setSceneFromMainWindow(CustomScene *myScene)
{
    this->scene = myScene;
}

void GuessSentenceSection::setMenu()
{
    setBorderRect();
    setSentenceAreas();
    setInputComponents();
    setButtons();
    setPoints();
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
    connect(buttonCheck,SIGNAL(clicked()),this,SLOT(checkSentence()));
    scene->addItem(buttonCheck);

    MyButton *buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(600,475,150,75);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonStart,SIGNAL(clicked()),this,SLOT(setSession()));
    scene->addItem(buttonStart);
}

void GuessSentenceSection::setPoints()
{

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

void GuessSentenceSection::setWordContainers()
{
    setColumn();
}

void GuessSentenceSection::setColumn()
{
    for (int y=0, n=1; y<n; ++y){
        setRow(y);
    }
}

void GuessSentenceSection::setRow(int y)
{
    Sentence *sentence = new Sentence();
    sentenceList.append(sentence);
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

void GuessSentenceSection::setInputComponents(){
    lineEdit = new QLineEdit();
    lineEdit->setFixedSize(800,50);
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
        //updateIndexOfSentenceInputByUserList(wordContainer);
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
    systemTime = new QTime();
    srand(time_t(systemTime));
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
        --indexOfWordContainerOnSentenceArea;//9
        updateIndexOfWordContainersOnSentenceArea(wordContainer->getIndexOnSentenceArea());//6
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
    //setSession();
}

void GuessSentenceSection::setSession()
{
    setVariables();
    setWordContainers();
    setSignNextWordContainerPositionToContainers();
}

void GuessSentenceSection::checkSentence()
{
    qDebug()<<"sprawdzamy";
    for (int i=0, n=sentenceInputByUserList.size(); i<n; ++i){
        qDebug()<<sentenceInputByUserList[i]<<" indeks "<<indexOfWordContainerOnSentenceArea;
    }
    if(sentenceList.last()->sentenceData.getCorrectSentence() == sentenceInputByUserList){
        qDebug()<<"zdanie jest poprawne!";
    }
    else qDebug()<<"zdanie nie jest poprawne!";
}

void GuessSentenceSection::back()
{
    scene->clear();
    //emit backButtonClicked();
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
    indexOfWordContainerOnSentenceArea = 0;
}




