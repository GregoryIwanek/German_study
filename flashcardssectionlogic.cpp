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

void FlashCardSectionLogic::setConnections(WordContainer *wcToConnect)
{
    connect(wcToConnect,SIGNAL(clicked(WordContainer*)),this,SLOT(setVisibilityAfterClick(WordContainer*)));
}

void FlashCardSectionLogic::setContainersOnScene()
{

}

void FlashCardSectionLogic::setNewSession()
{
    Sentence *sentence = new Sentence(QString("FCSection"), QString("FC_ANIMALS"));

    setWordsDefinition(sentence);
    setRandomListOrder(listOfWords);

    setRow(5,sentence);
}

void FlashCardSectionLogic::setWordsDefinition(Sentence *sentence)
{   /*Sets definition of words and their translations to display in WordContainers*/

    //24 times assign word and word translation to list ( for 48 WordContainers which will store these words)
    for (auto i=0; i<20; i++)
    {
        //define word as a word from given Sentence ( which already has 24 words and their translations)
        Word *wordGerman = new Word();
        wordGerman = sentence->sentenceDataPointer->getListOfWords()[i];
        wordGerman->setIfPickedToRandomListOfWords(false);
        Word *wordTranslation = new Word(*wordGerman);

        //set fonts so word will fit into WordContainer rectangle
        wordGerman->setWordFont(apperiance->fontComicSans_15);
        wordTranslation->setWordFont(apperiance->fontComicSans_15);

        //define if word is translation or origin word
        wordGerman->setIfIsTranslation(false);
        wordTranslation->setIfIsTranslation(true);

        //assign to lists
        listOfWords.append(wordGerman);
        listOfWords.append(wordTranslation);

        //is this necessary??????????????????
        ++count;
    }
}

void FlashCardSectionLogic::setRandomListOrder(QList<Word *> list)
{
    /*Sets words defined in listOfWords in random order */
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

void FlashCardSectionLogic::setRow(int rowNumber, Sentence *sentence)
{
    /*Sets rows of WordContainers*/
    for (auto i=0; i<rowNumber; ++i){
        setColumn(i);
    }
}

void FlashCardSectionLogic::setColumn(int rowIndex)
{
    /*Sets columns of WordCOntainers*/
    for (auto i=0, n=4; i<n; ++i){
        auto columnIndex = i;
        setFlashCards(columnIndex, rowIndex);
    }
}

void FlashCardSectionLogic::setFlashCards(int rowNumber, int columnNumber)
{
    //Defines WordContainers and Words in them
    WordContainer *wcGermanWord = new WordContainer(140,80,listOfWordsRandomOrder[2*countWordIndex],
            listOfWordsRandomOrder[2*countWordIndex]->getIfIsTranslation());
    WordContainer *wcGermanTranslation = new WordContainer(140,80,listOfWordsRandomOrder[2*countWordIndex+1],
            listOfWordsRandomOrder[2*countWordIndex+1]->getIfIsTranslation());

    //define sections which this containers belongs to
    wcGermanWord->setSectionItBelongsTo("FCSection");
    wcGermanTranslation->setSectionItBelongsTo("FCSection");

    //position them on scene
    scene->addItem(wcGermanWord);
    scene->addItem(wcGermanTranslation);
    wcGermanWord->setPos(QPointF(40+(2*rowNumber+1)*140, 40+columnNumber*80));
    wcGermanTranslation->setPos(QPointF(40+rowNumber*280, 40+columnNumber*80));

    //set connections of WordContainers
    setConnections(wcGermanWord);
    setConnections(wcGermanTranslation);

    //make text invisible at start
    setVisibilityOfWordContainers(wcGermanWord, wcGermanTranslation);

    //count index of added objects
    ++countWordIndex;
}

void FlashCardSectionLogic::setVisibilityOfWordContainers(WordContainer *wcGerman, WordContainer *wcTranslation)
{
    //make text invisible at start, will change later
    wcGerman->getWordPointerOfWordContainer()->setVisible(false);
    wcTranslation->getWordPointerOfWordContainer()->setVisible(false);
}

void FlashCardSectionLogic::setUncheckWordContainers(WordContainer *wcGerman, WordContainer *wcTranslation)
{
    //uncheck them, so we can click them again
    wcGerman->setIsChecked(false);
    wcTranslation->setIsChecked(false);
}

void FlashCardSectionLogic::setVisibilityAfterClick(WordContainer *wordContainerClicked)
{
    /*slot for switching visibility of text after we click on WordContainer, we can compare text of only two containers at same time,
        if it's not a case ( we have two visible texts) compare clicked WordContainers*/
    if (wordContainerClicked->getIfIsChecked() == false && listOfContainersToCompare.size() < 2)
    {
        //triggered two times before we go to condition below on third time
        wordContainerClicked->getWordPointerOfWordContainer()->setVisible(true);
        wordContainerClicked->setIsChecked(true);
        listOfContainersToCompare.append(wordContainerClicked);
    }
    else if (listOfContainersToCompare.size() == 2)
    {
        /*set text invisible and uncheck ( when WordContainers are different)
        -> this condition is triggered after we show 2x text, on third click*/
        setVisibilityOfWordContainers(listOfContainersToCompare[0], listOfContainersToCompare[1]);
        setUncheckWordContainers(listOfContainersToCompare[0], listOfContainersToCompare[1]);
        listOfContainersToCompare[0]->setColor(apperiance->brushDarkGray);
        listOfContainersToCompare[1]->setColor(apperiance->brushDarkGray);

        //clear list from objects after job is done
        listOfContainersToCompare.clear();
    }

    //triggered after we shown texts of two WordContainers
    if (listOfContainersToCompare.size() == 2)
    {
        setCompareClickedWordContainers();
    }
}

void FlashCardSectionLogic::setCompareClickedWordContainers()
{
    /*compare if word and translation of clicked 2 WordContainers are same*/
    if (listOfContainersToCompare[0]->getWordPointerOfWordContainer()->getText(false) ==
            listOfContainersToCompare[1]->getWordPointerOfWordContainer()->getText(false) &&
            (listOfContainersToCompare[0]->getWordPointerOfWordContainer()->getText(true) ==
             listOfContainersToCompare[1]->getWordPointerOfWordContainer()->getText(true)))
    {
        //set green color if true
        listOfContainersToCompare[0]->setColor(apperiance->brushGreen);
        listOfContainersToCompare[1]->setColor(apperiance->brushGreen);

        //make them immposible to click again
        listOfContainersToCompare.clear();
    }
    else
    {
        //set red color if incorrect
        listOfContainersToCompare[0]->setColor(apperiance->brushRed);
        listOfContainersToCompare[1]->setColor(apperiance->brushRed);
    }
}
