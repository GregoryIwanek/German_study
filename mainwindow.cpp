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

MainWindow::MainWindow()
{
    //sets main window of programm
    setMainWindow();
}

void MainWindow::setMainWindow()
{
    //sets scene of main window with fixed size of window
    scene = new CustomScene(this);
    scene->setSceneRect(0,0,1200,620);
    setFixedSize(1200,620);

    //sets view as a central widget
    view = new QGraphicsView(scene);
    setCentralWidget(view);

    //sets background image ( german flag)
    scene->setBackgroundBrush(apperiance->brushMainMenuTexture.texture().scaled(QSize(1200,620),Qt::IgnoreAspectRatio));

    //sets main menu buttons
    setMainMenu();
}

void MainWindow::setMainMenu()
{
    //defines every button in main menu, connects them to slot/signals and add to scene
    buttonStart = new MyButton();
    buttonStart->setGeometryOfButton(100,75,200,100);
    buttonStart->defineTextOfButton(QString("SENTENCE"), apperiance->brushDarkGray, apperiance->fontComicSans);
    connect(buttonStart,SIGNAL(clicked()),this,SLOT(setGuessSentenceSectionVisible()));
    scene->addItem(buttonStart);

    buttonFlashCards = new MyButton();
    buttonFlashCards->setGeometryOfButton(350,75,200,100);
    buttonFlashCards->defineTextOfButton(QString("FLASH CARDS"), apperiance->brushDarkGray, apperiance->fontComicSans);
    connect(buttonFlashCards,SIGNAL(clicked()),this,SLOT(setFlashCardSectionVisible()));
    scene->addItem(buttonFlashCards);

    buttonOptions = new MyButton();
    buttonOptions->setGeometryOfButton(100,250,200,100);
    buttonOptions->defineTextOfButton(QString("OPTIONS"), apperiance->brushRed, apperiance->fontComicSans);
    //connect(buttonOptions,SIGNAL(clicked()),this,SLOT(setGuessSentenceSectionVisible())); TODO later-> create small options section to set some options
    scene->addItem(buttonOptions);

    buttonQuit = new MyButton();
    buttonQuit->setGeometryOfButton(100,425,200,100);
    buttonQuit->defineTextOfButton(QString("QUIT"), apperiance->brushYellow, apperiance->fontComicSans);
    connect(buttonQuit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(buttonQuit);
}

void MainWindow::setGuessSentenceSectionVisible()
{
    //define GSSection after we click button "SENTENCE"
    //first clear scene from objects
    scene->clear();

    //steps to do to define instance of GSSection
    GuessSentenceSection *guessSentenceSection = new GuessSentenceSection();
    guessSentenceSection->setSceneFromMainWindow(scene);
    guessSentenceSection->setGuessSentenceSectionUI();
    guessSentenceSection->setGuessSentenceSectionLogic();
    guessSentenceSection->setConnectionsForSection();
    connect(this,SIGNAL(keyPressed(QKeyEvent*)),guessSentenceSection,SLOT(keyPressEvent(QKeyEvent*)));
    connect(guessSentenceSection->guessSentenceSectionUI,SIGNAL(signalBack(QObject*)),this,SLOT(setMainWindowVisible(QObject*)));
}

void MainWindow::setFlashCardSectionVisible()
{
    //define FCSection after we click button "FLASH CARDS"
    //first clear scene from objects
    scene->clear();

    //steps to do to define instane of FCSection
    FlashCardSection *flashCardSection = new FlashCardSection();
    flashCardSection->setSceneFromMainWindow(scene);
    flashCardSection->setFlashCardSectionUI();
    flashCardSection->setFlashCardSectionLogic();
    flashCardSection->setConnectionsForSection();
    connect(flashCardSection->flashCardSectionUI,SIGNAL(signalBack(QObject*)),this,SLOT(setMainWindowVisible(QObject*)));
}

void MainWindow::setMainWindowVisible(QObject *section)
{
    //recreate Main Window with interface after we click BACK in sections
    delete section;
    scene->clear();
    setMainMenu();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //simple keypress events-> passed down to GSSection
    emit keyPressed(event);
}
