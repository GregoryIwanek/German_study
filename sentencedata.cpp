#include "sentencedata.h"
#include "sentencescheme.h"
#include <QDebug>
#include <QList>
#include "apperiance.h"

extern Apperiance *apperiance;

SentenceData::SentenceData()
{
    setSchemeToWords();
    setRandomOrderList();
}

void SentenceData::setSentenceScheme()
{

}

void SentenceData::setSchemeToWords()
{
    for (size_t i=0, n=sentenceScheme.getRolesOfWordsInSentence().size(); i<n; ++i){

        Word *word = new Word();
        word->defineInstance(0,sentenceScheme.getRolesOfWordsInSentence()[i],
                             apperiance->fontComicSans,sentenceScheme.getQuerySQLList()[i],sentenceScheme.getIndexList()[i]);
        listOfWords.append(word);
    }
}

void SentenceData::setRandomOrderList()
{
    do{
        indexToPick = rand()%listOfWords.size();
        if(listOfWords[indexToPick]->getIfPickedToRandomListOfWords() == false ){
            listOfWordsRandomOrder.append(listOfWords[indexToPick]);
            numberOfPickedWordsToRandomList++;
            listOfWords[indexToPick]->setIfPickedToRandomListOfWords(true);
        }
    }while(numberOfPickedWordsToRandomList != listOfWords.size());
}

QList<Word*> SentenceData::getListOfWords()
{
    return listOfWords;
}

QList<Word *> SentenceData::getListOfWordsInRandomOrder()
{
    return listOfWordsRandomOrder;
}
