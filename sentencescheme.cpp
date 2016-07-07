#include "sentencescheme.h"
#include "QString"
#include <math.h>
#include <QDebug>

SentenceScheme::SentenceScheme()
{

}

SentenceScheme::SentenceScheme(QString sectionToPickFor, QString categoryOfWords)
{
    setBasicData(sectionToPickFor, categoryOfWords);
}

void SentenceScheme::setBasicData(QString sectionToPickFor, QString categoryOfWords)
{
    if (sectionToPickFor == "GSSection")
    {
        pickForFCSection = false;
        setDataForGuessSentence();
    }
    else if (sectionToPickFor == "FCSection")
    {
        pickForFCSection = true;
        setDataForFlashCard(categoryOfWords);
    }
}

void SentenceScheme::setDataForGuessSentence()
{
    setConnections();
    setVariables();
    setTypeOfSentence(true);
    setDefineExtraWords();
}

void SentenceScheme::setDataForFlashCard(QString categoryOfWords)
{
    setConnections();
    setVariables();
    setFlashCardList(categoryOfWords);
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

void SentenceScheme::setTypeOfSentence(bool complexSentenceAllowed)
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
    default:
        typeOfSentence = "rest";
        break;
    }
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
    algorythmNoun = new AlgorythmNoun(false);
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

    setCorrespondingSubjectSlot(algorythmNoun->getSubjectIndex());

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

void SentenceScheme::setWordAlgorythm(QString categoryOfWords)
{
    algorythmWord = new AlgorythmWord(categoryOfWords);
    setAlgorythm(algorythmWord->getQuery(), algorythmWord->getQueryTranslation(),algorythmWord->getWordIndex());
    increaseCount();
}

void SentenceScheme::setAlgorythm(QString queryWord, QString queryTranslation, int index, int indexTranslation)
{
    setQuerySQL(queryWord, NULL);
    setQuerySQL(NULL, queryTranslation);
    setIndex(index, indexTranslation);

    //FCSection Extras
    if (pickForFCSection == true)
    {
        setGender(algorythmWord->getQueryGender());
    }
}

void SentenceScheme::setGender(QString queryGender)
{
    querySQLGenderList.append(queryGender);
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

void SentenceScheme::setFlashCardList(QString categoryOfWords)
{
    //JUST FOR NOW!!! ToDo later-> create tables in SQLite speciefed for FCSection
    for (auto i=0; i<numberFCWordsToPick; ++i)
    {
        setWordAlgorythm(categoryOfWords);

        checkIfIndexAlreadyPicked();

        if (isIndexSQLAlreadyChosen == true) --i;

        setRemoveFromListsIfSameIndex();
    }
}

void SentenceScheme::setRemoveFromListsIfSameIndex()
{
    if (isIndexSQLAlreadyChosen == true)
    {
        querySQLList.removeLast();
        querySQLTranslationList.removeLast();
        querySQLGenderList.removeLast();
        indexList.removeLast();
        indexTranslationList.removeLast();

        isIndexSQLAlreadyChosen = false;
        --count;
    }
}

int SentenceScheme::getNumberOfExtraWords()
{
    return numberOfExtraWords;
}

bool SentenceScheme::checkIfIndexAlreadyPicked()
{
    for (auto i=0, n=indexList.size(); i<n-1; ++i)
    {
        if (indexList.last() == indexList[i] && indexList.size() != 1)
        {
            isIndexSQLAlreadyChosen = true;
        }
    }
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

QList<QString> SentenceScheme::getQuerySQLGenderList()
{
    return querySQLGenderList;
}
