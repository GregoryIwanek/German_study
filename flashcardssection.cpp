#include "flashcardssection.h"

FLashCardSection::FLashCardSection()
{

}

void FLashCardSection::setSceneFromMainWindow(CustomScene *myScene)
{
    scene = myScene;
}

void FLashCardSection::setFlashCardSectionUI()
{
    scene->clear();
    flashCardSectionUI = new FlashCardSectionUI();
    flashCardSectionUI->setSceneFromParent(scene);
    flashCardSectionUI->buildUI();
}

void FLashCardSection::setFlashCardSectionLogic()
{
    flashCardSectionLogic = new FlashCardSectionLogic();
    flashCardSectionLogic->setSceneFromParent(scene);
}

void FLashCardSection::setConnectionsSwitch(bool isConnected)
{

}

void FLashCardSection::setConnectionsForSection()
{

}

void FLashCardSection::keyPressEvent(QKeyEvent *event)
{

}

void FLashCardSection::switchConnections()
{

}
