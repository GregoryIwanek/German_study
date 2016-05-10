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
    scene->setSceneRect(0,0,1200,620);
    setFixedSize(1200,620);
    view = new QGraphicsView(scene);
    setCentralWidget(view);
    scene->setBackgroundBrush(apperiance->brushMainMenuTexture.texture().scaled(QSize(1200,620),Qt::IgnoreAspectRatio));
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


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}
