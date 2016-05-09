#include "algorythmnoun.h"
#include <stdlib.h>
#include <QDebug>

AlgorythmNoun::AlgorythmNoun()
{
    setInputFromSentenceScheme();
    setData();
}

void AlgorythmNoun::setInputFromSentenceScheme(int nounMaxIndex)
{
    nounIndex = nounMaxIndex;
}

void AlgorythmNoun::setData()
{
    defineVariables();
    defineNounArticle();
    defineNoun();
    defineTranslations();
}

void AlgorythmNoun::defineVariables()
{
    setIfIsSubject();
    setGrammarCase();
    setIfIsSingular();
    setIfIsDefined();
}

void AlgorythmNoun::setIfIsSubject(bool isNounASubject)
{
    isSentenceSubject = isNounASubject;
}

void AlgorythmNoun::setGrammarCase()
{
    if (isSentenceSubject == true){
        nounCase = "nominativ";
    }
    else nounCase = "dativ";
}

void AlgorythmNoun::setIfIsSingular()
{
    if (rand()%2 == 1){
        isSingular = true;
    }
    else isSingular = false;
}

void AlgorythmNoun::setIfIsDefined()
{
    if (rand()%2 == 1){
        isDefined = true;
    }
    else isDefined = false;
}

void AlgorythmNoun::defineNounArticle()
{
    setArticleSQLTable();
    setArticleIfSingular();
    setArticleIfDefined();
    setArticleSQLIndex();
    setArticleQuery();
}

void AlgorythmNoun::setArticleSQLTable()
{
    articleTable = "ARTICLE";
}

void AlgorythmNoun::setArticleIfSingular()
{
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
    //create query only when case is not true, becouse for PLURAR UNDEFINED nouns in german have NO ARTICLE, so we don't pick it
    if (nounArticleColumn != "plurar_undefined"){
        querySQLArticle = "SELECT " + nounArticleColumn +" FROM " + articleTable
                + " WITH(INDEX(" + QString::number(articleIndex) + "))";
    }

}

void AlgorythmNoun::defineNoun()
{
    setNounSQLTable();
    setNounColumn();
    setQueryForPickingIndex();
    setCorrespondingIndexResultsFromDataBase();
    setNounSQLIndex();
    setNounQuery();
}

void AlgorythmNoun::setNounSQLTable()
{
    nounTable = "NOUNS";
}

void AlgorythmNoun::setNounColumn()
{
    if (nounArticleColumn.contains("plurar")) {
        nounColumn = "plurarGerman";
    }
    else {
        nounColumn = "singularGerman";
    }
}

void AlgorythmNoun::setQueryForPickingIndex()
{
    querySQLNoun = "SELECT rowid FROM " + nounTable + " WHERE genderSingular = '" + nounGender + "'";
}

void AlgorythmNoun::setCorrespondingIndexResultsFromDataBase()
{
    QString result;
    query.exec(querySQLNoun);
    while (query.next()) {
        result = query.value(0).toString();
        indexListOfNouns.append(result.toInt());
    }
}

void AlgorythmNoun::setNounSQLIndex()
{
    //picking random word with correct grammar gender ( article and noun gender)
    int random = rand()%indexListOfNouns.size();
    nounIndex = indexListOfNouns[random];
    qDebug()<<nounIndex;
}

void AlgorythmNoun::setNounQuery()
{
    //we don't add condition "WHERE gender", beacouse we already have index with correct result from Table
    querySQLNoun = "SELECT " + nounColumn + " FROM " + nounTable;
}

void AlgorythmNoun::defineTranslations()
{
    setArticleTranslationQuery();
    setNounTranslationQuery();
}

void AlgorythmNoun::setArticleTranslationQuery()
{
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
    //first case ( combine english article and english word to get one expression from two,
    //beacouse in german there is no article ( just word)
    if (isSingular != true && isDefined != true){
        querySQLNounTranslation = "SELECT articleUndefined || ' ' || plurarEnglish FROM " + nounTable;
    }
    else if (isSingular != true && isDefined == true){
        querySQLNounTranslation = "SELECT plurarEnglish FROM " + nounTable;
    }
    else if ((isSingular == true && isDefined != true) || (isSingular == true && isDefined == true)){
        querySQLNounTranslation = "SELECT singularEnglish FROM " + nounTable;
    }
}


QString AlgorythmNoun::getQueries()
{
    return querySQLArticle, querySQLArticleTranslation, querySQLNoun, querySQLNounTranslation;
}

int AlgorythmNoun::getQueriesRowsIndex()
{
    return articleIndex, nounIndex;
}
