#include "flashcardssectionlogic.h"
#include "wordcontainer.h"
#include "apperiance.h"
#include "QDebug"

extern Apperiance *apperiance;

FlashCardSectionLogic::FlashCardSectionLogic()
{

}

void FlashCardSectionLogic::setSceneFromParent(CustomScene *myScene)
{
    scene = myScene;
}

void FlashCardSectionLogic::setContainersOnScene()
{

}

void FlashCardSectionLogic::setNewSession()
{
    Sentence *sentence = new Sentence(QString("FCSection"), QString("FC_ANIMALS"));
    for (auto i=0; i<24; i++)
    {
        Word *wordGerman = new Word();
        wordGerman = sentence->sentenceDataPointer->getListOfWords()[i];
        wordGerman->setIfPickedToRandomListOfWords(false);
        Word *wordTranslation = new Word(*wordGerman);
        wordGerman->setWordFont(apperiance->fontComicSans_15);
        wordTranslation->setWordFont(apperiance->fontComicSans_15);
        wordGerman->setIfIsTranslation(false);
        wordTranslation->setIfIsTranslation(true);
        listOfWords.append(wordGerman);
        listOfWords.append(wordTranslation);

        ++count;
    }
    setRandomListOrder(listOfWords);

    setRow(6,sentence);
}

void FlashCardSectionLogic::setRow(int rowNumber, Sentence *sentence)
{
    for (auto i=0; i<rowNumber; ++i){
        setColumn(i,sentence);
    }
}

void FlashCardSectionLogic::setColumn(int rowIndex, Sentence *sentence)
{
    for (auto i=0, n=4; i<n; ++i){
        auto columnIndex = i;
        setFlashCards(columnIndex, rowIndex, sentence, count);
    }
}

void FlashCardSectionLogic::setRandomListOrder(QList<Word *> list)
{
    setALoop(list);
}

void FlashCardSectionLogic::setALoop(QList<Word *> list)
{
    do{
        indexToPick = rand()%list.size();
        if (list[indexToPick]->getIfPickedToRandomListOfWords() == false)
        {
            listOfWordsRandomOrder.append(list[indexToPick]);
            ++numberOfPickedWordsToRandomList;
            list[indexToPick]->setIfPickedToRandomListOfWords(true);
        }
    } while (numberOfPickedWordsToRandomList != list.size());

}

void FlashCardSectionLogic::setConnections(Word *myWord)
{

}

void FlashCardSectionLogic::setFlashCards(int rowNumber, int columnNumber, Sentence *sentence, int count)
{
    WordContainer *wcGermanWord = new WordContainer(140,60,listOfWordsRandomOrder[2*countWordIndex],
            listOfWordsRandomOrder[2*countWordIndex]->getIfIsTranslation());
    WordContainer *wcGermanTranslation = new WordContainer(140,60,listOfWordsRandomOrder[2*countWordIndex+1],
            listOfWordsRandomOrder[2*countWordIndex+1]->getIfIsTranslation());

    scene->addItem(wcGermanWord);
    scene->addItem(wcGermanTranslation);
    wcGermanWord->setPos(QPointF(40+(2*rowNumber+1)*140, 40+columnNumber*60));
    wcGermanTranslation->setPos(QPointF(40+rowNumber*280, 40+columnNumber*60));

    ++countWordIndex;
}

void FlashCardSectionLogic::setColorOfWordContainer(WordContainer *wordContainer)
{
    if (1)
        //if singular
    {
        if (1)
        {
            //if masculine
            wordContainer->setColor(apperiance->brushBlue);
        }
        else if (1)
        {
            //if feminine
            wordContainer->setColor(apperiance->brushGreen);
        }
        else if (1)
        {
            //if neutral
            wordContainer->setColor(apperiance->brushCyan);
        }
    }
    else //if plurar
    {
        wordContainer->setColor(apperiance->brushYellow);
    }
}

