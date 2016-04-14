#include "sentencedata.h"
#include "sentencescheme.h"
#include <QDebug>
#include <QList>
#include "apperiance.h"

extern Apperiance *apperiance;

SentenceData::SentenceData()
{
    setSchemeToWords();
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

QList<Word*> SentenceData::getListOfWords()
{
    return listOfWords;
}
