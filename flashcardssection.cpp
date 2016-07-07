#include "flashcardssection.h"

FlashCardSection::FlashCardSection()
{

}

void FlashCardSection::setSceneFromMainWindow(CustomScene *myScene)
{
    //setting main scene as a scene to draw on
    scene = myScene;
}

void FlashCardSection::setFlashCardSectionUI()
{
    //sets UI of FCSection and basic definition
    scene->clear();
    flashCardSectionUI = new FlashCardSectionUI();
    flashCardSectionUI->setParent(this);
    flashCardSectionUI->setSceneFromParent(scene);
    flashCardSectionUI->buildUI();
}

void FlashCardSection::setFlashCardSectionLogic()
{
    //sets logic section of FCSection
    flashCardSectionLogic = new FlashCardSectionLogic();
    flashCardSectionLogic->setParent(this);
    flashCardSectionLogic->setSceneFromParent(scene);
}

void FlashCardSection::setConnectionsSwitch(bool isConnected)
{

}

void FlashCardSection::setConnectionsForSection()
{
    //sets all kind connections in FCSection, between FCSectionUI/FCSectionLogic

    connect(flashCardSectionUI->getMyButton("buttonStart"),SIGNAL(clicked()),flashCardSectionLogic,SLOT(setNewSession()));
    connect(flashCardSectionUI->getMyButton("buttonClear"),SIGNAL(clicked()),flashCardSectionLogic,SLOT(resetSession()));

    connect(flashCardSectionUI->getMyButton("buttonBack"),SIGNAL(clicked()),flashCardSectionUI,SLOT(back()));
}

void FlashCardSection::keyPressEvent(QKeyEvent *event)
{

}

void FlashCardSection::switchConnections()
{

}
