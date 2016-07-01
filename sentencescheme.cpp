#include "sentencescheme.h"
#include "QString"
#include <math.h>
#include <QDebug>

SentenceScheme::SentenceScheme()
{
    setData();
}

SentenceScheme::SentenceScheme(QString definedTypeOfSentence)
{
    //setConnections();
    //setVariables();
    setTypeOfSentence(true, definedTypeOfSentence);
    setDefineExtraWords();
}

void SentenceScheme::setData()
{
    setConnections();
    setVariables();
    setTypeOfSentence(true);
    setDefineExtraWords();
}

void SentenceScheme::setConnections()
{
    //connect(algorythmPerson,SIGNAL(subjectType(int)),this,SLOT(setCorrespondingSubjectSlot(int)));
}

void SentenceScheme::setVariables()
{
    numberOfSubsentenceses = 1;
    numberOfExtraWords = 0;
    count=0;
}

void SentenceScheme::setTypeOfSentence(bool complexSentenceAllowed, QString definedTypeOfSentence)
{
    if (definedTypeOfSentence == NULL)
    {
        int type;
        if (complexSentenceAllowed == true){
            type = qrand()%2;
        }
        else type = 0;
        switch(type){
        case 0:
            typeOfSentence = "declarative";
            setDeclarativeSentence();
            break;
        case 1:
            typeOfSentence = "complex";
            setComplexSentence();
            break;
        case 2:
            typeOfSentence = "negative";
            setNegativeSentence();
            break;
        case 3:
            typeOfSentence = "interrogative";
            setInterrogativeSentence();
            break;
        case 4:
            typeOfSentence = "interrogative";
            setInterrogativeSentence();
            break;
        case 5:
            typeOfSentence = "flashCardList";
            setFlashCardList();
            break;
        default:
            typeOfSentence = "rest";
            break;
        }
    }
    else typeOfSentence = definedTypeOfSentence;
}

void SentenceScheme::setDeclarativeSentence()
{
    int sequence = qrand()%2;
    switch (sequence) {
    case 0:
        setPersonAlgorythm();
        setVerbAlgorythm();
        setNounAlgorythm();
        break;
    case 1:
        setNounAlgorythmAsSubject();
        setVerbAlgorythm();
        setNounAlgorythm();
    }
}

void SentenceScheme::setNegativeSentence()
{
    setPersonAlgorythm();
}

void SentenceScheme::setInterrogativeSentence()
{

}

void SentenceScheme::setExpression()
{

}

void SentenceScheme::setComplexSentence()
{
    numberOfSubsentenceses = rand()%2+1;

    for (auto i=0, n=numberOfSubsentenceses; i<n; ++i){
        setTypeOfSentence(false);

        if (i < numberOfSubsentenceses-1){
            setSeparatorAlgorythm();
        }
    }
}

void SentenceScheme::setFlashCardList()
{

}

void SentenceScheme::setPersonAlgorythm()
{
    algorythmPerson = new AlgorythmPerson();
    setCorrespondingSubjectSlot(algorythmPerson->getPersonIndex());
    setAlgorythm(algorythmPerson->getQuery(),algorythmPerson->getQueryTranslation(),algorythmPerson->getPersonIndex());
    increaseCount();
}

void SentenceScheme::setVerbAlgorythm()
{
    algorythmVerb = new AlgorythmVerb(correspondingSubjectPerson);
    setAlgorythm(algorythmVerb->getQuery(),algorythmVerb->getQueryTranslation(),algorythmVerb->getVerbIndex());
    increaseCount();
}

void SentenceScheme::setNounAlgorythm()
{
    algorythmNoun = new AlgorythmNoun();
    if (algorythmNoun->getQueryArticle() != NULL){
        setAlgorythm(algorythmNoun->getQueryArticle(),algorythmNoun->getQueryArticleTranslation(),
                     algorythmNoun->getQueryArticleRowIndex(),algorythmNoun->getQueryNounRowIndex());
        increaseCount();
    }
    setAlgorythm(algorythmNoun->getQueryNoun(),algorythmNoun->getQueryNounTranslation(),algorythmNoun->getQueryNounRowIndex());
    increaseCount();
}

void SentenceScheme::setNounAlgorythmAsSubject()
{
    algorythmNoun = new AlgorythmNoun(true);

    setCorrespondingSubjectSlot(3);

    if (algorythmNoun->getQueryArticle() != NULL){
        setAlgorythm(algorythmNoun->getQueryArticle(),algorythmNoun->getQueryArticleTranslation(),
                     algorythmNoun->getQueryArticleRowIndex(),algorythmNoun->getQueryNounRowIndex());
        increaseCount();
    }
    setAlgorythm(algorythmNoun->getQueryNoun(),algorythmNoun->getQueryNounTranslation(),algorythmNoun->getQueryNounRowIndex());
    increaseCount();
}

void SentenceScheme::setSeparatorAlgorythm()
{
    algorythmSeparator = new AlgorythmSeparator();
    setAlgorythm(algorythmSeparator->getQuery(),algorythmSeparator->getQueryTranslation(),algorythmSeparator->getSeparatorIndex());
    increaseCount();
}

void SentenceScheme::setAlgorythm(QString queryWord, QString queryTranslation, int index, int indexTranslation)
{
    setQuerySQL(queryWord, NULL);
    setQuerySQL(NULL, queryTranslation);
    setIndex(index, indexTranslation);
}

void SentenceScheme::setQuerySQL(QString columnWord, QString columnTranslation)
{
    if (columnWord != NULL){
        querySQLList.append(columnWord);
        incrementNumberOfExtraWords();
    }
    else if (columnTranslation != NULL) {
        querySQLTranslationList.append(columnTranslation);
    }
}

void SentenceScheme::incrementNumberOfExtraWords()
{
    if (addingExtraWords == true){
        ++numberOfExtraWords;
    }
}

void SentenceScheme::setIndex(int indexWord, int indexTranslation)
{
    if (indexTranslation < 0){
        indexList.append(indexWord);
        indexTranslationList.append(indexWord);
    }
    else {
        indexList.append(indexWord);
        indexTranslationList.append(indexTranslation);
    }
}

void SentenceScheme::increaseCount()
{
    ++count;
}

void SentenceScheme::setDefineExtraWords()
{
    addingExtraWords = true;

    for (auto i=0, n=numberOfSubsentenceses; i<n; ++i){
        setExtraWords();
    }
}

void SentenceScheme::setExtraWords()
{
    int number = rand()%4;
    
    for (auto i=0, n=number; i<n; ++i){
        int pickWord = rand()%3;
        switch (pickWord){
        case 0:
            setPersonAlgorythm();
            break;
        case 1:
            setVerbAlgorythm();
            break;
        case 2:
            setNounAlgorythm();
            break;
        case 3:
            setSeparatorAlgorythm();
            break;
        }
    }
}

int SentenceScheme::getNumberOfExtraWords()
{
    return numberOfExtraWords;
}

QList<int> SentenceScheme::getIndexList(bool returnIndexList)
{
    if (returnIndexList == true){
        return indexList;
    }
    else return indexTranslationList;
}

int SentenceScheme::getNumberOfWords()
{
    return count;
}

void SentenceScheme::setCorrespondingSubjectSlot(int personIndex)
{
    correspondingSubjectPerson = personIndex;
}

QList<QString> SentenceScheme::getQuerySQLList(bool returnQuerySQLList)
{
    if (returnQuerySQLList == true){
        return querySQLList;
    }
    else return querySQLTranslationList;
}
