#include "guesssentencesection.h"
#include <QDebug>

GuessSentenceSection::GuessSentenceSection()
{

}

void GuessSentenceSection::setSceneFromMainWindow(CustomScene *myScene)
{
    scene = myScene;
}

void GuessSentenceSection::setGuessSentenceSectionUI()
{
    scene->clear();
    guessSentenceSectionUI = new GuessSentenceSectionUI();
    guessSentenceSectionUI->setParent(this);
    guessSentenceSectionUI->setSceneFromParent(scene);
    guessSentenceSectionUI->buildUI();
}

void GuessSentenceSection::setGuessSentenceSectionLogic()
{
    guessSentenceSectionLogic = new GuessSentenceSectionLogic();
    guessSentenceSectionLogic->setParent(this);
    guessSentenceSectionLogic->setSceneFromParent(scene);
    guessSentenceSectionLogic->setSentenceAreaList(guessSentenceSectionUI->getSentenceAreaList());
}

void GuessSentenceSection::setConnectionsSwitch(bool isConnected)
{
    connectionsSwitch = isConnected;
}

void GuessSentenceSection::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}

void GuessSentenceSection::switchConnections()
{
    if (connectionsSwitch == true){
        disconnect(this,SIGNAL(keyPressed(QKeyEvent*)),guessSentenceSectionLogic,SLOT(keyPressEvent(QKeyEvent*)));
        setConnectionsSwitch(false);
    }
    else {
        connect(this,SIGNAL(keyPressed(QKeyEvent*)),guessSentenceSectionLogic,SLOT(keyPressEvent(QKeyEvent*)));
        setConnectionsSwitch(true);
    }
}

void GuessSentenceSection::setConnectionsForSection()
{
    connect(this,SIGNAL(keyPressed(QKeyEvent*)),guessSentenceSectionLogic,SLOT(keyPressEvent(QKeyEvent*)));

    connect(guessSentenceSectionUI->getMyLineEdit(),SIGNAL(returnPressed()),guessSentenceSectionUI,SLOT(sendLineEditData()));

    connect(guessSentenceSectionUI,SIGNAL(signalSendLineEditData(QString)),guessSentenceSectionLogic,SLOT(checkIfSentenceIsCorrectInLineEdit(QString)));
    connect(guessSentenceSectionUI->getMyButton("buttonClear"),SIGNAL(clicked()),guessSentenceSectionLogic,SLOT(clearSentence()));
    connect(guessSentenceSectionUI->getMyButton("buttonCheck"),SIGNAL(clicked()),guessSentenceSectionLogic,SLOT(checkIfSentenceIsCorrect()));
    connect(guessSentenceSectionUI->getMyButton("buttonStart"),SIGNAL(clicked()),guessSentenceSectionLogic,SLOT(setNewSentence()));
    connect(guessSentenceSectionUI->getMyButton("buttonHint"),SIGNAL(hoverEvent()),guessSentenceSectionUI,SLOT(showHideHint()));
    connect(guessSentenceSectionUI->getMyButton("buttonBack"),SIGNAL(clicked()),guessSentenceSectionUI,SLOT(back()));

    connect(guessSentenceSectionLogic,SIGNAL(sentenceCreated(QString)),guessSentenceSectionUI,SLOT(updateSentenceText(QString)));
    connect(guessSentenceSectionLogic,SIGNAL(pointsChanged(int)),guessSentenceSectionUI,SLOT(updatePointsText(int)));
    connect(guessSentenceSectionLogic,SIGNAL(resultChanged(bool)),guessSentenceSectionUI,SLOT(updateResultText(bool)));
    connect(guessSentenceSectionLogic,SIGNAL(clearUITexts(bool)),guessSentenceSectionUI,SLOT(clearUIText(bool)));
}
