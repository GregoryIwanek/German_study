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
    //sets section to pick for
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
    //steps to set data for GSSection
    setConnections();
    setVariables();
    setTypeOfSentence(true);
    setDefineExtraWords();
}

void SentenceScheme::setDataForFlashCard(QString categoryOfWords)
{
    //steps to set data for FCSection
    setConnections();
    setVariables();
    setFlashCardList(categoryOfWords);
}

void SentenceScheme::setConnections()
{
    //to do later
    //connect(algorythmPerson,SIGNAL(subjectType(int)),this,SLOT(setCorrespondingSubjectSlot(int)));
}

void SentenceScheme::setVariables()
{
    //sets default values of variables
    numberOfSubsentenceses = 1;
    numberOfExtraWords = 0;
    count=0;
}

void SentenceScheme::setTypeOfSentence(bool complexSentenceAllowed)
{
    //sets type of sentence, random-> right now only complex and declarative sentence-> rest to do later
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
    //sets declarative sentence, when noun (cat, dog etc.) is subject or person (I, you etc.) is a subject
    int sequence = qrand()%2;

    switch (sequence){
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
    //sets algorythm for person ( I, you, he etc.)-> creates data and SQL query to pick it form database
    setPersonAlgorythm();
}

void SentenceScheme::setInterrogativeSentence()
{
    //TODO later-> scheme of interrogative sentence (question)
}

void SentenceScheme::setExpression()
{
    //TODO later-> scheme of expression ( not sentence, ready expression like "Hi, how are you?"
}

void SentenceScheme::setComplexSentence()
{
    //steps to create scheme for sentence which is build from two or more subsentences
    numberOfSubsentenceses = rand()%2+1;
    
    for (auto i=0, n=numberOfSubsentenceses; i<n; ++i)
    {
        setTypeOfSentence(false);
        
        //if there is a subsentence, create SQL query for separator ( like "and, or, although etc.)
        if (i < numberOfSubsentenceses-1)
        {
            setSeparatorAlgorythm();
        }
    }
}

void SentenceScheme::setPersonAlgorythm()
{
    //sets final algorythm for person (I, you, he etc)
    algorythmPerson = new AlgorythmPerson();

    //picks column in SQL table depending on grammar case of subject
    setCorrespondingSubjectSlot(algorythmPerson->getPersonIndex());

    //sets queries to proper list ( german word query and translation query) for use in SentenceData
    setAlgorythm(algorythmPerson->getQuery(),algorythmPerson->getQueryTranslation(),algorythmPerson->getPersonIndex());

    //increase count of words
    increaseCount();
}

void SentenceScheme::setVerbAlgorythm()
{
    //sets final verb algorythm
    algorythmVerb = new AlgorythmVerb(correspondingSubjectPerson);

    //adds queries to lists and corresponding index lists
    setAlgorythm(algorythmVerb->getQuery(),algorythmVerb->getQueryTranslation(),algorythmVerb->getVerbIndex());
    increaseCount();
}

void SentenceScheme::setNounAlgorythm()
{
    //sets final noun algorythm when noun is not a subject of sentence
    algorythmNoun = new AlgorythmNoun(false);

    //sets algorythm depending on if there is article in a word or not ( a, an, the, der die das etc.)->
    //some words in translation have article while german words don't
    if (algorythmNoun->getQueryArticle() != NULL){
        setAlgorythm(algorythmNoun->getQueryArticle(),algorythmNoun->getQueryArticleTranslation(),
                     algorythmNoun->getQueryArticleRowIndex(),algorythmNoun->getQueryNounRowIndex());
        increaseCount();
    }

    //sets algorythm while there is no article and assign queries to lists
    setAlgorythm(algorythmNoun->getQueryNoun(),algorythmNoun->getQueryNounTranslation(),algorythmNoun->getQueryNounRowIndex());

    //incerase count of words
    increaseCount();
}

void SentenceScheme::setNounAlgorythmAsSubject()
{
    //sets final noun algorythm when it is subject of the sentence
    algorythmNoun = new AlgorythmNoun(true);
    
    //gets index which holds correct result
    setCorrespondingSubjectSlot(algorythmNoun->getSubjectIndex());
    
    //sets if there is an article in word
    if (algorythmNoun->getQueryArticle() != NULL){
        setAlgorythm(algorythmNoun->getQueryArticle(),algorythmNoun->getQueryArticleTranslation(),
                     algorythmNoun->getQueryArticleRowIndex(),algorythmNoun->getQueryNounRowIndex());
        increaseCount();
    }

    //sets if there is no article in word
    setAlgorythm(algorythmNoun->getQueryNoun(),algorythmNoun->getQueryNounTranslation(),algorythmNoun->getQueryNounRowIndex());
    increaseCount();
}

void SentenceScheme::setSeparatorAlgorythm()
{
    //sets separator algorythm ( and, also, or etc)
    algorythmSeparator = new AlgorythmSeparator();
    setAlgorythm(algorythmSeparator->getQuery(),algorythmSeparator->getQueryTranslation(),algorythmSeparator->getSeparatorIndex());
    increaseCount();
}

void SentenceScheme::setWordAlgorythm(QString categoryOfWords)
{
    //sets algorythm for picking word for FCSection only, with translation
    algorythmWord = new AlgorythmWord(categoryOfWords);
    setAlgorythm(algorythmWord->getQuery(), algorythmWord->getQueryTranslation(),algorythmWord->getWordIndex());
    increaseCount();
}

void SentenceScheme::setAlgorythm(QString queryWord, QString queryTranslation, int index, int indexTranslation)
{
    //assigns SQL queries and indexs to correct lists
    setQuerySQL(queryWord, NULL);
    setQuerySQL(NULL, queryTranslation);
    setIndex(index, indexTranslation);
    
    //ONLY for FCSection-> picks extra information from SQL
    if (pickForFCSection == true)
    {
        //gets gender of a word
        setGender(algorythmWord->getQueryGender());
    }
}

//APPENDS to list of queries

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

void SentenceScheme::incrementNumberOfExtraWords()
{
    //increase number of extra words after we call for new extra word
    if (addingExtraWords == true)
    {
        ++numberOfExtraWords;
    }
}

void SentenceScheme::increaseCount()
{
    ++count;
}

void SentenceScheme::setDefineExtraWords()
{
    //steps to define algorythm for extra words in sentences for GSSection ( extra WordContainers with words)
    addingExtraWords = true;
    
    for (auto i=0, n=numberOfSubsentenceses; i<n; ++i)
    {
        setExtraWords();
    }
}

void SentenceScheme::setExtraWords()
{
    //sets extra word randomly
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
    //ONLY for FCSection-> if word was picked twice, remove it form lists and decrease count
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

//GETTERS

int SentenceScheme::getNumberOfExtraWords()
{
    return numberOfExtraWords;
}

void SentenceScheme::checkIfIndexAlreadyPicked()
{
    //checks if index was picked ( if there is same word two times on list)
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
