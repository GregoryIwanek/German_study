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
#include "customscene.h"
#include "QTime"
#include <stdlib.h>
#include "sentence.h"
#include "mybutton.h"
extern Apperiance *apperiance;

MainWindow::MainWindow(){
    setMainWindow();
}

void MainWindow::setMainWindow(){
    scene = new CustomScene(this);
    scene->setSceneRect(0,0,1200,600);
    setFixedSize(1200,600);
    view = new QGraphicsView(scene);
    setCentralWidget(view);
    scene->setBackgroundBrush(apperiance->brushMainMenuTexture.texture().scaled(QSize(1200,600),Qt::IgnoreAspectRatio));
    setMainMenu();
}

void MainWindow::setMainMenu()
{
    MyButton *buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(100,75,200,100);
    buttonStart->defineTextOfButton(QString("START"), apperiance->brushDarkGray, apperiance->fontComicSans);
    connect(buttonStart,SIGNAL(clicked()),this,SLOT(setGuessSentenceSectionVisible()));
    scene->addItem(buttonStart);

    MyButton *buttonOptions = new MyButton();
    buttonOptions->setGeometryOfButton(100,250,200,100);
    buttonOptions->defineTextOfButton(QString("OPTIONS"), apperiance->brushRed, apperiance->fontComicSans);
    connect(buttonOptions,SIGNAL(clicked()),this,SLOT(setGuessSentenceSectionVisible()));
    scene->addItem(buttonOptions);

    MyButton *buttonQuit = new MyButton();
    buttonQuit->setGeometryOfButton(100,425,200,100);
    buttonQuit->defineTextOfButton(QString("QUIT"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonQuit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(buttonQuit);
}

void MainWindow::setGuessSentenceSectionMenu()
{

}

void MainWindow::setGuessSentenceSectionVisible()
{
    scene->clear();
    guessSentenceSection = new GuessSentenceSection();
    guessSentenceSection->setSceneFromMainWindow(scene);
    guessSentenceSection->setGuessSentenceSectionUI();
    guessSentenceSection->setGuessSentenceSectionLogic();
    guessSentenceSection->setConnectionsForSection();
    connect(this,SIGNAL(keyPressed(QKeyEvent*)),guessSentenceSection,SLOT(keyPressEvent(QKeyEvent*)));
}

void MainWindow::setSession()
{
    setWordContainers();
    setVariables();
}

void MainWindow::setBorderRect(){
    QVector<QPointF> borderPointsOuter;
    borderPointsOuter << getClosestGridPoint(QPointF(20,20)) << getClosestGridPoint(QPointF(20,580))
                      << getClosestGridPoint(QPointF(1180,580)) << getClosestGridPoint(QPointF(1180,20));
    QVector<QPointF> borderPointsInner;
    borderPointsInner << getClosestGridPoint(QPointF(40,40)) << getClosestGridPoint(QPointF(40,560))
                      << getClosestGridPoint(QPointF(1160,560)) << getClosestGridPoint(QPointF(1160,40));

    QPolygonF borderRectangleOuter(borderPointsOuter);
    scene->addPolygon(borderRectangleOuter);
    QPolygonF borderRectangleInner(borderPointsInner);
    scene->addPolygon(borderRectangleInner);
}

void MainWindow::setWordContainers(){
    setColumn();
}

void MainWindow::setSentenceAreas(){
    //create areas to put rects with words in
    for (int i=0, n=2; i<n; ++i){
        SentenceArea *sentenceArea = new SentenceArea();
        sentenceArea->setPos(60,60+i*sentenceArea->boundingRect().height());
        scene->addItem(sentenceArea);
        sentenceArea->setWordContainerStartPosition(sentenceArea->pos());
        sentenceAreaList.append(sentenceArea);
    }
}

void MainWindow::setInputComponents(){
    lineEdit = new QLineEdit();
    lineEdit->setFixedSize(800,50);
    //scene->addWidget(lineEdit);
}

void MainWindow::setColumn(){
    Sentence *sentence = new Sentence();
    for (int y=0, n=sentence->sentenceData.getListOfWords().size(); y<n; ++y){
        setRow(y, sentence->sentenceData.getListOfWords()[y]);
    }
}

void MainWindow::setRow(int y, Word *myWord){
    for (int x=0, n=5; x<n; ++x){
        WordContainer *wordContainer = new WordContainer(myWord);
        wordContainer->setPos(QPointF(60+x*(wordContainer->boundingRect().width()+20), 240 + y*(wordContainer->boundingRect().height()+20)));
        wordContainer->setStartPosition(wordContainer->pos());
        //checkWordContainerCollision(wordContainer->getStartPosition());
        scene->addItem(wordContainer);
        wordContainerList.append(wordContainer);
        connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
    }
}

void MainWindow::setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved)
{
    if (isWordContainerMoved == true){
        nextWordContainerPosition.setX(nextWordContainerPosition.x() + wordContainer->boundingRect().width()+19);
        nextWordContainerPosition.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
    }
    else {
        nextWordContainerPosition.setX(nextWordContainerPosition.x() - wordContainer->getWidthOfRect()-19);
        nextWordContainerPosition.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
    }
}

void MainWindow::setVariables()
{
    nextWordContainerPosition = QPointF(sentenceAreaList.first()->getWordContainerStartPosition().x()+20,
                                        sentenceAreaList.first()->getWordContainerStartPosition().y());
    systemTime = new QTime();
    srand(time_t(systemTime));
}

void MainWindow::checkWordContainerCollision(QPointF startPointOfChecked)
{
    QPointF startingPoint = startPointOfChecked;
    for (int i=0, n=wordContainerList.size(); i<n; ++i){
        if (typeid(*(wordContainerList[i])) == typeid(WordContainer))
        {
            wordContainerList[i]->setPos(QPointF(startingPoint.x()+20,startingPoint.y()+20));
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}

QPointF MainWindow::getClosestGridPoint(QPointF point)
{
    return this->scene->getGridPoint(point);
}

void MainWindow::sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer){
    if (wordContainer->getIsOnSentenceArea()==false) {
        //send to sentenceArea
        wordContainer->setPos(nextWordContainerPosition);
        wordContainer->setIsOnSentenceArea(true);
        setNextWordContainerPosition(wordContainer,true);
    }
    else {
        //send back
        wordContainer->setPos(wordContainer->getStartPosition());
        wordContainer->setIsOnSentenceArea(false);
        setNextWordContainerPosition(wordContainer,false);
    }
}

