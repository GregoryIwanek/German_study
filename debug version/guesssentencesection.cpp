#include "guesssentencesection.h"
#include <QDebug>

GuessSentenceSection::GuessSentenceSection()
{

}

void GuessSentenceSection::setSceneFromMainWindow(CustomScene *myScene)
{
    //sets main scene as a secene to draw on
    scene = myScene;
}

void GuessSentenceSection::setGuessSentenceSectionUI()
{
    //sets UI of GSSection and basic definitions
    scene->clear();
    guessSentenceSectionUI = new GuessSentenceSectionUI();
    guessSentenceSectionUI->setParent(this);
    guessSentenceSectionUI->setSceneFromParent(scene);
    guessSentenceSectionUI->buildUI();
}

void GuessSentenceSection::setGuessSentenceSectionLogic()
{
    //sets Logic of GSSection and basic definitions
    guessSentenceSectionLogic = new GuessSentenceSectionLogic();
    guessSentenceSectionLogic->setParent(this);
    guessSentenceSectionLogic->setSceneFromParent(scene);
    guessSentenceSectionLogic->setSentenceAreaList(guessSentenceSectionUI->getSentenceAreaList());
}

void GuessSentenceSection::keyPressEvent(QKeyEvent *event)
{
    //standard key press event, passed to Logic by emitting signal
    emit keyPressed(event);
}

void GuessSentenceSection::setConnectionsForSection()
{
    //sets all type of connections beetwen Logic and UI in GSSection

    connect(this,SIGNAL(keyPressed(QKeyEvent*)),guessSentenceSectionLogic,SLOT(keyPressEvent(QKeyEvent*)));

    connect(guessSentenceSectionUI->getMyLineEdit(),SIGNAL(returnPressed()),guessSentenceSectionUI,SLOT(sendLineEditData()));

    //UI to Logic
    connect(guessSentenceSectionUI,SIGNAL(signalSendLineEditData(QString)),guessSentenceSectionLogic,SLOT(checkIfSentenceIsCorrectInLineEdit(QString)));
    connect(guessSentenceSectionUI->getMyButton("buttonClear"),SIGNAL(clicked()),guessSentenceSectionLogic,SLOT(clearSentence()));
    connect(guessSentenceSectionUI->getMyButton("buttonCheck"),SIGNAL(clicked()),guessSentenceSectionLogic,SLOT(checkIfSentenceIsCorrect()));
    connect(guessSentenceSectionUI->getMyButton("buttonStart"),SIGNAL(clicked()),guessSentenceSectionLogic,SLOT(setNewSentence()));
    connect(guessSentenceSectionUI->getMyButton("buttonHint"),SIGNAL(hoverEvent()),guessSentenceSectionUI,SLOT(showHideHint()));
    connect(guessSentenceSectionUI->getMyButton("buttonBack"),SIGNAL(clicked()),guessSentenceSectionUI,SLOT(back()));

    //Logic to UI
    connect(guessSentenceSectionLogic,SIGNAL(sentenceCreated(QString)),guessSentenceSectionUI,SLOT(updateSentenceText(QString)));
    connect(guessSentenceSectionLogic,SIGNAL(pointsChanged(int)),guessSentenceSectionUI,SLOT(updatePointsText(int)));
    connect(guessSentenceSectionLogic,SIGNAL(resultChanged(bool)),guessSentenceSectionUI,SLOT(updateResultText(bool)));
    connect(guessSentenceSectionLogic,SIGNAL(clearUITexts(bool)),guessSentenceSectionUI,SLOT(clearUIText(bool)));
}
