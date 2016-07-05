#include "sentencedata.h"
#include "sentencescheme.h"
#include <QDebug>
#include <QList>
#include "apperiance.h"

extern Apperiance *apperiance;

SentenceData::SentenceData()
{

}

SentenceData::SentenceData(const SentenceData &sentenceData)
{

}

SentenceData::SentenceData(QString sectionToPickFor, QString categoryOfWords)
{
    setSentenceScheme(sectionToPickFor, categoryOfWords);
    setSchemeToWords();
    setRandomOrderList();
    setSentenceAndTranslation();
}

void SentenceData::checkSectionToPickFor(QString sectionToPickFor)
{
    if (sectionToPickFor == "FCSection")
    {
        pickForFCSection = true;
    }
    else pickForFCSection = false;
}

void SentenceData::setSentenceScheme(QString sectionToPickFor, QString categoryOfWords)
{
    sentenceSchemePointer = new SentenceScheme(sectionToPickFor, categoryOfWords);
}

void SentenceData::setSchemeToWords()
{
    for (auto i=0, n=sentenceSchemePointer->getNumberOfWords(); i<n; ++i){
        Word *word = new Word();
        word->defineInstance(0, apperiance->fontComicSans,
                             sentenceSchemePointer->getQuerySQLList(true)[i],sentenceSchemePointer->getIndexList(true)[i],
                             sentenceSchemePointer->getQuerySQLList(false)[i], sentenceSchemePointer->getIndexList(false)[i]);

        if (pickForFCSection == true)
        {
            word->pickExtraInfoFromSQL(sentenceSchemePointer->getQuerySQLGenderList()[i], i);
        }

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
    for (auto i=0, n = listOfWords.size()-sentenceSchemePointer->getNumberOfExtraWords(); i<n; ++i){
        listCorrectSentence.append(listOfWords[i]->getText(false));
        correctSentenceString.append(listOfWords[i]->getText(false)+QString(" "));
    }
    correctSentenceString.remove(correctSentenceString.length()-1,1);

    for (auto i=0, n = listOfWords.size()-sentenceSchemePointer->getNumberOfExtraWords(); i<n; ++i){
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
