#include "algorythmword.h"
#include <QDebug>

AlgorythmWord::AlgorythmWord(QString categoryOfWords)
{
    setWordSQLTable(categoryOfWords);
    setData();
}

void AlgorythmWord::setData()
{
    defineWord();
    defineTranslation();
    defineGender();

}

void AlgorythmWord::defineWord()
{
    defineVariables();
    setWordSQLColumn();
    setWordSQLRow();
    setWordQuery();
}

void AlgorythmWord::defineVariables()
{
    setIfSingular();
}

void AlgorythmWord::setIfSingular()
{
    int x = rand()%2;

    if (x == 0){
        isSingular = true;
    }
    else isSingular = false;
}

void AlgorythmWord::setWordSQLTable(QString table)
{
    wordTable = table;
}

void AlgorythmWord::setWordSQLColumn()
{
    if (isSingular == true)
    {
        wordColumn = "singularGerman";
    }
    else wordColumn = "plurarGerman";
}

void AlgorythmWord::setWordSQLRow()
{
    wordIndex = rand()%30;
}

void AlgorythmWord::setWordQuery()
{
    querySQLWord = "SELECT " + wordColumn + " FROM " + wordTable;
}

void AlgorythmWord::defineTranslation()
{
    setWordTranslationSQLColumn();
    setWordTranslationQuery();
}

void AlgorythmWord::setWordTranslationSQLColumn()
{
    if (isSingular == true)
    {
        wordTranslationColumn = "singularEnglish";
    }
    else wordTranslationColumn = "plurarEnglish";
}

void AlgorythmWord::setWordTranslationQuery()
{
    querySQLWordTranslation = "SELECT " + wordTranslationColumn + " FROM " + wordTable;
}

void AlgorythmWord::defineGender()
{
    setGenderSQLColumn();
    setGenderSQLQuery();
}

void AlgorythmWord::setGenderSQLColumn()
{
    if (isSingular == true){
        genderColumn = "genderSingular";
    }
    else genderColumn = "none";
}

void AlgorythmWord::setGenderSQLQuery()
{
    if (isSingular == true)
    {
        querySQLGender = "SELECT " + genderColumn + " FROM " + wordTable;
    }
    else querySQLGender = "PLURAR_IS_FEMININE";
}

QString AlgorythmWord::getQuery()
{
    return querySQLWord;
}

QString AlgorythmWord::getQueryTranslation()
{
    return querySQLWordTranslation;
}

QString AlgorythmWord::getQueryGender()
{
    return querySQLGender;
}

int AlgorythmWord::getWordIndex()
{
    return  wordIndex;
}

bool AlgorythmWord::getIfIsSingular()
{
    return isSingular;
}
