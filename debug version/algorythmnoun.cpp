#include "algorythmnoun.h"
#include <stdlib.h>
#include <QDebug>

AlgorythmNoun::AlgorythmNoun(bool isNounASubject)
{
    setIfIsSubject(isNounASubject);
    setData();
}

void AlgorythmNoun::setData()
{
    //series of steps to define every aspect of noun to pick from SQL
    defineVariables();
    defineNounArticle();
    defineNoun();
    defineTranslations();
}

void AlgorythmNoun::defineVariables()
{
    //series of steps to set all possible variables of noun
    setGrammarCase();
    setIfIsSingular();
    setIfIsDefined();
    setSubjectIndex();
}

void AlgorythmNoun::setIfIsSubject(bool isNounASubject)
{
    //sets if noun is a subject of the sentence ex. the CAT drinks milk
        isSentenceSubject = isNounASubject;
}

void AlgorythmNoun::setGrammarCase()
{
    //sets grammar case of the noun ( in german-> 4 cases, like in Polish)
    if (isSentenceSubject == true){
        nounCase = "nominativ";
    }
    else nounCase = "akkusativ";
}

void AlgorythmNoun::setIfIsSingular()
{
    //define if noun is singular or plurar
    if (rand()%2 == 1){
        isSingular = true;
    }
    else isSingular = false;
}

void AlgorythmNoun::setIfIsDefined()
{
    //define if is defined or not ( difference between a/an/the and ein/eine/einen/der/die/das)
    if (rand()%2 == 1){
        isDefined = true;
    }
    else isDefined = false;
}

void AlgorythmNoun::setSubjectIndex()
{
    //only if noun is a subject in the sentence!!!
    //sets index of row in SQL base, so we can pick correct version of a verb
    if (isSentenceSubject == true){
        if (isSingular == true){
            subjectIndex = 3; //case "third person", he, she, it
        }
        else subjectIndex = 7; //case "they"
    }
}

void AlgorythmNoun::defineNounArticle()
{
    //series of steps to define article (a/an/the ein/eine...) of the noun
    setArticleSQLTable();
    setArticleIfSingular();
    setArticleIfDefined();
    setArticleSQLIndex();
    setArticleQuery();
}

void AlgorythmNoun::setArticleSQLTable()
{
    //sets SQL table to pick from
    articleTable = "ARTICLE";
}

void AlgorythmNoun::setArticleIfSingular()
{
    //sets first part of article SQL column depending on if it's for singular word or plurar
    int article;
    article = rand()%3;

    if (isSingular == true){
        switch (article) {
        case 0:
            nounArticleColumn = "masculine_";
            setArticleAndNounGender("masculine");
            break;
        case 1:
            nounArticleColumn = "feminine_";
            setArticleAndNounGender("feminine");
            break;
        case 2:
            nounArticleColumn = "neutral_";
            setArticleAndNounGender("neutral");
            break;
        }
    }
    else nounArticleColumn = "plurar_";
}

void AlgorythmNoun::setArticleIfDefined()
{
    //sets second part of SQL column to pick from, depending on if it's DEFINED word or UNDEFINED
    if (isDefined == true){
        nounArticleColumn.append("defined");
        setArticleAndNounGender(NULL);
    }
    else {
        nounArticleColumn.append("undefined");
        setArticleAndNounGender(NULL);
    }
}

void AlgorythmNoun::setArticleAndNounGender(QString gender)
{
    //set gender of ARTICLE and NOUN depending if was already defined and if noun is plurar/singular
    if (isSingular == true && gender != NULL){
        nounGender = gender;
    }
    else if (isSingular != true){
        //roll gender if NOUN is PLURAR
        int number = rand()%3;
        switch (number){
        case 0: nounGender = "masculine";
            break;
        case 1: nounGender = "feminine";
            break;
        case 2: nounGender = "neutral";
            break;
        }
    }
}

void AlgorythmNoun::setArticleSQLIndex()
{
    //set index of row in SQL to pick from ( depending on grammar case)
    if (nounCase == "nominativ"){
        articleIndex = 0;
    }
    else if (nounCase == "genitiv"){
        articleIndex = 1;
    }
    else if (nounCase == "dativ"){
        articleIndex = 2;
    }
    else if (nounCase == "akkusativ"){
        articleIndex = 3;
    }
}

void AlgorythmNoun::setArticleQuery()
{
    //create query only when case is not true, becouse for PLURAR UNDEFINED nouns in german there are have NO ARTICLE, so we don't pick it
    if (nounArticleColumn != "plurar_undefined"){
        querySQLArticle = "SELECT " + nounArticleColumn +" FROM " + articleTable;
    }

}

void AlgorythmNoun::defineNoun()
{
    //series of steps to define noun
    setNounSQLTable();
    setNounColumn();
    setQueryForPickingIndex();
    setCorrespondingIndexResultsFromDataBase();
    setNounSQLIndex();
    setNounQuery();
}

void AlgorythmNoun::setNounSQLTable()
{
    //sets noun SQL table to pick from
    nounTable = "NOUNS";
}

void AlgorythmNoun::setNounColumn()
{
    //sets column in SQL to pick from depending on if word is plurar/singular
    if (nounArticleColumn.contains("plurar")) {
        nounColumn = "plurarGerman";
    }
    else {
        nounColumn = "singularGerman";
    }
}

void AlgorythmNoun::setQueryForPickingIndex()
{
    //sets query for picking index which holds corresponding correct nouns to our case/gender/number etc.
    querySQLNoun = "SELECT rowid FROM " + nounTable + " WHERE genderSingular = '" + nounGender + "'";
}

void AlgorythmNoun::setCorrespondingIndexResultsFromDataBase()
{
    //picks correct indexs and save them in a list for later use
    QString result;
    query.exec(querySQLNoun);
    while (query.next()) {
        result = query.value(0).toString();
        indexListOfNouns.append(result.toInt()-1);
    }
}

void AlgorythmNoun::setNounSQLIndex()
{
    //picking random word wich has correct grammar, gender and number ( article and noun gender)
    int random = rand()%indexListOfNouns.size();
    nounIndex = indexListOfNouns[random];
}

void AlgorythmNoun::setNounQuery()
{
    //we don't add condition "WHERE gender", beacouse we already have index with correct result from Table
    //we overide querySQLNoun QString here and define final query to use outside that class
    querySQLNoun = "SELECT " + nounColumn + " FROM " + nounTable;
}

void AlgorythmNoun::defineTranslations()
{
    //steps to define translation
    setArticleTranslationQuery();
    setNounTranslationQuery();
}

void AlgorythmNoun::setArticleTranslationQuery()
{
    //define query for translation depending on if noun is defined/singular
    if (isDefined == true){
        querySQLArticleTranslation = "SELECT articleDefined FROM " + nounTable;
    }
    //we dodge case when isPlurar and isUndefined ( explanation in setNounTranslationQuery())
    else if (isSingular == true && isDefined != true){
        querySQLArticleTranslation = "SELECT articleUndefined FROM " + nounTable;
    }
}

void AlgorythmNoun::setNounTranslationQuery()
{
    //sets final query for translation
    /*first case ( combine english article and english word to get one expression from two words,
    beacouse in german there is no article for plurar undefined( just a single word)*/
    if (isSingular != true && isDefined != true){
        querySQLNounTranslation = "SELECT articleUndefined || ' ' || plurarEnglish FROM " + nounTable;
        isQueryArticleNounCombined = true;
    }
    else if (isSingular != true && isDefined == true){
        querySQLNounTranslation = "SELECT plurarEnglish FROM " + nounTable;
    }
    else if ((isSingular == true && isDefined != true) || (isSingular == true && isDefined == true)){
        querySQLNounTranslation = "SELECT singularEnglish FROM " + nounTable;
    }
}

//GETTERS

QString AlgorythmNoun::getQueryArticle()
{
    return getIfPlurarUndefined(querySQLArticle);
}

QString AlgorythmNoun::getQueryArticleTranslation()
{
    return getIfPlurarUndefined(querySQLArticleTranslation);
}

QString AlgorythmNoun::getQueryNoun()
{
    return querySQLNoun;
}

QString AlgorythmNoun::getQueryNounTranslation()
{
    return querySQLNounTranslation;
}

QString AlgorythmNoun::getIfPlurarUndefined(QString toReturn)
{
    if (nounArticleColumn != "plurar_undefined"){
        return toReturn;
    }
    else return NULL;
}

int AlgorythmNoun::getQueryArticleRowIndex()
{
    if (nounArticleColumn != "plurar_undefined"){
        return articleIndex;
    }
    else return NULL;
}

int AlgorythmNoun::getQueryNounRowIndex()
{
    return nounIndex;
}

int AlgorythmNoun::getSubjectIndex()
{
    //only if noun is a subject, mathod is called from sentenceScheme.cpp
    return subjectIndex;
}


