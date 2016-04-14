#include "sentencescheme.h"
#include "QString"
#include <math.h>
#include <QDebug>
SentenceScheme::SentenceScheme(){

    setTypeOfSentence();
}

void SentenceScheme::updateScheme(QString update)
{
    rolesOfWordsInSentence.append(update);
}

void SentenceScheme::setIndex(int max)
{
    indexList.append(rand()%max);
    qDebug()<<rand()%max;
}

QList<int> SentenceScheme::getIndexList()
{
    return indexList;
}

void SentenceScheme::setTypeOfSentence()
{
    int type = 1;
    switch(type){
    case 1:
        typeOfSentence = "declarative";
        setDeclarativeSentence();
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
        typeOfSentence = "complex";
        setComplexSentence();
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

}

void SentenceScheme::setSubjectData()
{
    setSubjectTypeSQLTable(); //direct or non-direct_subject
    setSubjectType();
    setIndex(1);
    setQuerySQL(subjectType);
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

        subjectIndexDirect = rand()%8;
        switch (subjectIndexDirect){
        case 0: subjectType = "ich";
            break;
        case 1: subjectType = "du";
            break;
        case 2: subjectType = "er";
            break;
        case 3: subjectType = "sie";
            break;
        case 4: subjectType = "es";
            break;
        case 5: subjectType = "wir";
            break;
        case 6: subjectType = "ihr";
            break;
        case 7: subjectType = "Sie[3]";
            break;
        }
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
    verbType = "";
}

void SentenceScheme::setVerbData()
{
    setVerbTypeSQLTable();
    setVerbType();
    setIndex(7);
    setQuerySQL(subjectType);
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
            nounType = "singularG_der_die_das";
        }
        else{
            nounType = "singularG_ein_eine_einem";
        }
    }
    else {
        if (isNounDefined == true){
            nounType = "plurarG_der_die_das";
        }
        else {
            nounType = "plurarG_ein_eine_einem";
        }
    }
}

void SentenceScheme::setNounData()
{
    setNounTypeSQLTable();
    setNounType();
    setIndex(10);
    setQuerySQL(nounType);
}

QList<QString> SentenceScheme::getRolesOfWordsInSentence()
{
    return rolesOfWordsInSentence;
}

void SentenceScheme::setQuerySQL(QString column)
{
    querySQL = QString("SELECT") + " " + column + " FROM " +rolesOfWordsInSentence[count];
    querySQLList.append(querySQL);
    ++count;
    qDebug()<<querySQLList[count-1];
}

QString SentenceScheme::getQuerySQL()
{
    return querySQL;
}

QList<QString> SentenceScheme::getQuerySQLList()
{
    return querySQLList;
}
