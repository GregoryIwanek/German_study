#include "mainwindow.h"
#include "wordcontainer.h"
#include "sentencearea.h"
#include "apperiance.h"
#include <QDebug>
#include <QVector>
#include <QGraphicsPolygonItem>

extern Apperiance *aperiance;

MainWindow::MainWindow(){
    setMainWindow();
    setBorderRect();
    setWordContainers();
    setSentenceAreas();
    setVariables();
}

void MainWindow::setMainWindow(){    
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1200,600);
    setFixedSize(1200,600);
    scene->setBackgroundBrush(apperiance->brushRed);
    view = new QGraphicsView(scene);
    setCentralWidget(view);
}

void MainWindow::setBorderRect(){
    QVector<QPointF> borderPointsOuter;
    borderPointsOuter << QPointF(0,0) << QPointF(0,600) << QPointF(1200,600) << QPointF(1200,0);
    QVector<QPointF> borderPointsInner;
    borderPointsInner << QPointF(50,50) << QPointF(50,550) << QPointF(1150,550) << QPointF(1150,50);

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
    for (int i=0, n=3; i<n; ++i){
        SentenceArea *sentenceArea = new SentenceArea();
        sentenceArea->setPos(50,50+i*sentenceArea->boundingRect().height());
        scene->addItem(sentenceArea);
        sentenceArea->setWordContainerStartPosition(sentenceArea->pos());
        sentenceAreaList.append(sentenceArea);
    }
}

void MainWindow::setColumn(){
    for (int i=0, n=3; i<n; ++i){
        setRow(i);
    }
}

void MainWindow::setRow(int y){
    for (int i=0, n=5; i<n; ++i){
        WordContainer *wordContainer = new WordContainer();
        wordContainer->setPos(100+i*(wordContainer->boundingRect().width()+10),250 + y*wordContainer->boundingRect().height());
        wordContainer->setStartPosition(wordContainer->pos());
        scene->addItem(wordContainer);
        connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
    }
}

void MainWindow::setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved){
    if (isWordContainerMoved == true){
        nextWordContainerPosition.setX(nextWordContainerPosition.x() + wordContainer->getWidthOfRect()+15);
        nextWordContainerPosition.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
    }
    else {
        nextWordContainerPosition.setX(nextWordContainerPosition.x() - wordContainer->getWidthOfRect()-15);
        nextWordContainerPosition.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
    }
}

void MainWindow::setVariables(){
    nextWordContainerPosition = sentenceAreaList.first()->getWordContainerStartPosition();
}

void MainWindow::sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer){
    if (wordContainer->getIsMoved()==false) {
        //send to sentenceArea
        wordContainer->setPos(nextWordContainerPosition);
        wordContainer->setIsMoved(true);
        setNextWordContainerPosition(wordContainer,true);
    }
    else {
        //send back
        wordContainer->setPos(wordContainer->getStartPosition());
        wordContainer->setIsMoved(false);
        setNextWordContainerPosition(wordContainer,false);
    }
}

