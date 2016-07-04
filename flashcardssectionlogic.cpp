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
    Sentence *sentence = new Sentence(QString("FCSection"), QString("COLOURS"));
    for (auto i=0, n=8; i<n; ++i){
        auto columnIndex = i;
        setFlashCards(columnIndex, rowIndex, sentence, count);
        ++count;
    }
}

void FlashCardSectionLogic::setFlashCards(int rowNumber, int columnNumber, Sentence *sentence, int count)
{
    Word *word = new Word();
    word = sentence->sentenceDataPointer->getListOfWords()[count];
    qDebug()<<count;
    qDebug()<<sentence->sentenceDataPointer->getListOfWords()[count]->getText(false);
    WordContainer *wc = new WordContainer(140,60,word);
    scene->addItem(wc);
    wc->setPos(QPointF(40+rowNumber*140, 40+columnNumber*60));
}


