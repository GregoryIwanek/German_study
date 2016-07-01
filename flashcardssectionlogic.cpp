#include "flashcardssectionlogic.h"
#include "wordcontainer.h"
#include "QDebug"

FlashCardSectionLogic::FlashCardSectionLogic()
{

}

void FlashCardSectionLogic::setSceneFromParent(CustomScene *myScene)
{
    scene = myScene;
}

void FlashCardSectionLogic::setNewSession()
{
    setRow(6);
}

void FlashCardSectionLogic::setRow(int rowNumber)
{
    for (auto i=0; i<rowNumber; ++i){
        setColumn(i);
    }
}

void FlashCardSectionLogic::setColumn(int rowIndex)
{
    for (auto i=0, n=8; i<n; ++i){
        sentence = new Sentence();
        auto columnIndex = i;
        setFlashCards(columnIndex, rowIndex, sentence);
    }
}

void FlashCardSectionLogic::setFlashCards(int rowNumber, int columnNumber, Sentence *sentence)
{
    Word *word = new Word();
    WordContainer *wc = new WordContainer(140,60,word);
    scene->addItem(wc);
    wc->setPos(QPointF(40+rowNumber*140, 40+columnNumber*60));
}


