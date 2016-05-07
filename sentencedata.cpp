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
    setSentenceAndTranslation();
}

void SentenceData::setSentenceScheme()
{

}

void SentenceData::setSchemeToWords()
{
    for (size_t i=0, n=sentenceScheme.getRolesOfWordsInSentence().size(); i<n; ++i){

        Word *word = new Word();
        word->defineInstance(0,sentenceScheme.getRolesOfWordsInSentence()[i],
                             apperiance->fontComicSans,sentenceScheme.getQuerySQLList(true)[i],sentenceScheme.getIndexList(true)[i],
                             sentenceScheme.getQuerySQLList(false)[i], sentenceScheme.getIndexList(false)[i]);
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

void SentenceData::setSentenceAndTranslation()
{
    for (size_t i=0, n = listOfWords.size()-sentenceScheme.getNumberOfExtraWords(); i<n; ++i){
        listCorrectSentence.append(listOfWords[i]->getText(false));
        correctSentenceString.append(listOfWords[i]->getText(false)+QString(" "));
    }
    correctSentenceString.remove(correctSentenceString.length()-1,1);

    for (size_t i=0, n = listOfWords.size()-sentenceScheme.getNumberOfExtraWords(); i<n; ++i){
        correctTranslationString.append(listOfWords[i]->getText(true)+QString(" "));
    }
}

QList<Word*> SentenceData::getListOfWords()
{
    return listOfWords;
}

QList<Word *> SentenceData::getListOfWordsInRandomOrder()
{
    return listOfWordsRandomOrder;
}

QList<QString> SentenceData::getCorrectSentence()
{
    return listCorrectSentence;
}

QString SentenceData::getCorrectTranslationString()
{
    return correctTranslationString;
}

QString SentenceData::getCorrectSentenceString()
{
    return correctSentenceString;
}
