#include "algorythmnoun.h"
#include <stdlib.h>
#include <QDebug>

AlgorythmNoun::AlgorythmNoun()
{
setArticleSQLIndex();
}

void AlgorythmNoun::setData()
{
    defineVariables();
    defineNounArticle();
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

void AlgorythmNoun::setNounSQLTable()
{
        nounTable = "NOUN";
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
    setArticleIfSingular();
    setArticleIfDefined();
}

void AlgorythmNoun::setArticleSQLTable()
{
    articleTable = "ARTICLE";
}

void AlgorythmNoun::setArticleIfSingular()
{
    int article;
    article = rand()%3;

    if (isSingular == false){
        switch (article) {
        case 0:
            nounArticleColumn = "masculine_";
            break;
        case 1:
            nounArticleColumn = "feminine_";
            break;
        case 2:
            nounArticleColumn = "neutral_";
            break;
        }
    }
    else nounArticleColumn = "plurar_";
}

void AlgorythmNoun::setArticleIfDefined()
{
    if (isDefined == true){
        nounArticleColumn.append("defined");
    }
    else nounArticleColumn.append("undefined");
}

void AlgorythmNoun::setArticleSQLIndex()
{
    if (nounCase == "nominativ") articleIndex = 0;
    else if (nounCase == "genitiv") articleIndex = 1;
    else if (nounCase == "dativ") articleIndex = 2;
    else if (nounCase == "akkusativ") articleIndex = 3;
}
