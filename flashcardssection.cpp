#include "flashcardssection.h"

FlashCardSection::FlashCardSection()
{

}

void FlashCardSection::setSceneFromMainWindow(CustomScene *myScene)
{
    scene = myScene;
}

void FlashCardSection::setFlashCardSectionUI()
{
    scene->clear();
    flashCardSectionUI = new FlashCardSectionUI();
    flashCardSectionUI->setParent(this);
    flashCardSectionUI->setSceneFromParent(scene);
    flashCardSectionUI->buildUI();
}

void FlashCardSection::setFlashCardSectionLogic()
{
    flashCardSectionLogic = new FlashCardSectionLogic();
    flashCardSectionLogic->setParent(this);
    flashCardSectionLogic->setSceneFromParent(scene);
}

void FlashCardSection::setConnectionsSwitch(bool isConnected)
{

}

void FlashCardSection::setConnectionsForSection()
{
    connect(flashCardSectionUI->getMyButton("buttonStart"),SIGNAL(clicked()),flashCardSectionLogic,SLOT(setNewSession()));
    connect(flashCardSectionUI->getMyButton("buttonBack"),SIGNAL(clicked()),flashCardSectionUI,SLOT(back()));
}

void FlashCardSection::keyPressEvent(QKeyEvent *event)
{

}

void FlashCardSection::switchConnections()
{

}
