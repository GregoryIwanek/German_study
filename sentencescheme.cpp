#include "sentencescheme.h"
#include "QString"
#include <math.h>
#include <QDebug>

SentenceScheme::SentenceScheme(){

    setVariables();
    setTypeOfSentence(true);
    setDefineExtraWords();
}

void SentenceScheme::updateScheme(QString update)
{
    rolesOfWordsInSentence.append(update);
}

void SentenceScheme::setDefineExtraWords()
{
    for (size_t i=0, n=numberOfSubsentenceses; i<n; ++i){
        setExtraWords();
    }
}

void SentenceScheme::setVariables()
{
    numberOfSubsentenceses = 1;
    numberOfExtraWords = 0;
    count=0;
}

void SentenceScheme::setExtraWords()
{
    int number = rand()%3;

    for (size_t i=0, n=number; i<n; ++i){
        int pickWord = rand()%3;
        switch (pickWord){
        case 0:
            setSubjectData();
            break;
        case 1:
            setVerbData();
            break;
        case 2:
            setNounData();
            break;
        }
        ++numberOfExtraWords;
    }
}

int SentenceScheme::getNumberOfExtraWords()
{
    return numberOfExtraWords;
}

void SentenceScheme::setIndex(int max)
{
    indexList.append(rand()%(max));
    indexTranslationList.append(indexList.last());
}

QList<int> SentenceScheme::getIndexList(bool returnIndexList)
{
    if (returnIndexList == true){
        return indexList;
    }
    else return indexTranslationList;
}

void SentenceScheme::increaseCount()
{
    ++count;
}

void SentenceScheme::setTypeOfSentence(bool complexSentenceAllowed)
{
    int type;
    if (complexSentenceAllowed == true){
        type = rand()%2;
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
    default:
        typeOfSentence = "rest";
        break;
    }
}

void SentenceScheme::setDeclarativeSentence()
{
    setSubjectData();
    setVerbData();
    setNounData();
}

void SentenceScheme::setNegativeSentence()
{
    if (isSubjectDirect == true){
        rolesOfWordsInSentence.append(QString("DIRECT_SUBJECT"));
    }
    else {
        rolesOfWordsInSentence.append(QString("NON_DIRECT_SUBJECT"));
    }
    rolesOfWordsInSentence.append(QString("NO"));
    rolesOfWordsInSentence.append(QString("VERB"));
    rolesOfWordsInSentence.append(QString("NOUN"));
}

void SentenceScheme::setInterrogativeSentence()
{
    rolesOfWordsInSentence.append(QString("VERB"));

    if (isSubjectDirect == true){
        rolesOfWordsInSentence.append(QString("DIRECT_SUBJECT"));
    }
    else {
        rolesOfWordsInSentence.append(QString("NON_DIRECT_SUBJECT"));
    }

    rolesOfWordsInSentence.append(QString("NOUN"));
}

void SentenceScheme::setComplexSentence()
{
    numberOfSubsentenceses = rand()%2+1;

    for (size_t i=0, n=numberOfSubsentenceses; i<n; ++i){
        setTypeOfSentence(false);

        if (i < numberOfSubsentenceses-1){
            setSeparator();
        }
    }
}

void SentenceScheme::setSubjectData()
{
    setSubjectTypeSQLTable(); //direct or non-direct_subject
    setSubjectType();
    setIndex(8);
    setQuerySQL(subjectType, NULL);
    setSubjectTranslation();
    increaseCount();
}

void SentenceScheme::setSubjectTranslation()
{
    setQuerySQL(NULL, QString("translation"));
}

void SentenceScheme::setSubjectTypeSQLTable()
{
    isSubjectDirect = true;

    if (isSubjectDirect == true){
        subjectTable = "DIRECT_SUBJECT";
        updateScheme(subjectTable);
    }
    else {
        subjectTable = "NON_DIRECT_SUBJECT";
        updateScheme(subjectTable);
    }
}

void SentenceScheme::setSubjectType()
{
    if (subjectTable == "DIRECT_SUBJECT"){

        subjectType = "word";
    }
    else {

        singularPlurarIfNonDirect = rand()%3;
        switch (singularPlurarIfNonDirect){
        case 0:
            break;
        case 1: ;
            break;
        case 2:
            break;
        }
        subjectIndexIfNonDirect = rand()%3;
    }
}

void SentenceScheme::setVerbTypeSQLTable()
{
    updateScheme(QString("VERB_ANIMALS"));
}

void SentenceScheme::setVerbType()
{    
    switch (indexList.last()){
    case 0: verbType = "ich";
        break;
    case 1: verbType = "du";
        break;
    case 2: verbType = "er";
        break;
    case 3: verbType = "sie";
        break;
    case 4: verbType = "es";
        break;
    case 5: verbType = "wir";
        break;
    case 6: verbType = "ihr";
        break;
    case 7: verbType = "sie_3";
        break;
    }
}

void SentenceScheme::setVerbData()
{
    setVerbTypeSQLTable();
    setVerbType();
    setIndex(28);
    setQuerySQL(verbType, NULL);
    setVerbTranslation();
    increaseCount();
}

void SentenceScheme::setVerbTranslation()
{
    setQuerySQL(NULL, QString("translation"));
}

void SentenceScheme::setNounTypeSQLTable()
{
    updateScheme(QString("NOUN"));
}

void SentenceScheme::setNounType()
{
    setIfNounSingular();
    setIfNounDefined();
    setSQLColumn();
}

void SentenceScheme::setIfNounSingular()
{
    if (rand()%2 == 1){
        isNounSingular = true;
    }
    else isNounSingular = false;
}

void SentenceScheme::setIfNounDefined()
{
    if (rand()%2 == 1){
        isNounDefined = true;
    }
    else isNounDefined = false;
}

void SentenceScheme::setSQLColumn()
{
    if (isNounSingular == true){
        if (isNounDefined == true) {
            nounType = "singularG_nominativ_der_die_das";
            nounTypeSwitch = 0;
        }
        else{
            nounType = "singularG_nominativ_ein_eine_einem";
            nounTypeSwitch = 1;
        }
    }
    else {
        if (isNounDefined == true){
            nounType = "plurarG_der_die_das";
            nounTypeSwitch = 2;
        }
        else {
            nounType = "plurarG_ein_eine_einem";
            nounTypeSwitch = 3;
        }
    }
}

void SentenceScheme::setNounData()
{
    setNounTypeSQLTable();
    setNounType();
    setIndex(30);
    setQuerySQL(nounType, NULL);
    setNounTranslation();
    increaseCount();
}

void SentenceScheme::setNounTranslation()
{
    QString translationColumn;

    switch (nounTypeSwitch) {
    case 0: translationColumn = "singularThe";
        break;
    case 1: translationColumn = "singularA";
        break;
    case 2: translationColumn = "plurarThe";
        break;
    case 3: translationColumn = "plurarA";
        break;
    default:
        break;
    }

    setQuerySQL(NULL, translationColumn);
}

void SentenceScheme::setSeparator()
{
    setSeparatorTypeSQLTable();
    setSeparatorType();
    setIndex(5);
    setQuerySQL(separatorType,NULL);
    setSeparatorTranslation();
    increaseCount();
}

void SentenceScheme::setSeparatorTypeSQLTable()
{
    updateScheme(QString("SEPARATORS"));
}

void SentenceScheme::setSeparatorType()
{
    separatorType = "word";
}

void SentenceScheme::setSeparatorTranslation()
{
    setQuerySQL(NULL,QString("translation"));
}

QList<QString> SentenceScheme::getRolesOfWordsInSentence()
{
    return rolesOfWordsInSentence;
}

void SentenceScheme::setQuerySQL(QString columnWord, QString columnTranslation)
{
    if (columnWord != NULL){
        querySQL = QString("SELECT") + " " + columnWord + " FROM " +rolesOfWordsInSentence[count];
        querySQLList.append(querySQL);
        qDebug()<<querySQL;
    }
    else if (columnTranslation != NULL) {
        querySQLTranslation = QString("SELECT") + " " + columnTranslation + " FROM " +rolesOfWordsInSentence[count];
        querySQLTranslationList.append(querySQLTranslation);
        qDebug()<<querySQLTranslation;
    }
}

QString SentenceScheme::getQuerySQL()
{
    return querySQL;
}

QList<QString> SentenceScheme::getQuerySQLList(bool returnQuerySQLList)
{
    if (returnQuerySQLList == true){
        return querySQLList;
    }
    else return querySQLTranslationList;
}
