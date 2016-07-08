#include "algorythmword.h"
#include <QDebug>

AlgorythmWord::AlgorythmWord(QString categoryOfWords)
{
    //sets words to pick for FCSection, depending on category of words ( to do)
    setWordSQLTable(categoryOfWords);
    setData();
}

void AlgorythmWord::setData()
{
    //series of steps to define word to pick and it's translation and gender
    defineWord();
    defineTranslation();
    defineGender();

}

void AlgorythmWord::defineWord()
{
    //steps to define word to pick
    defineVariables();
    setWordSQLColumn();
    setWordSQLRow();
    setWordQuery();
}

void AlgorythmWord::defineVariables()
{
    //define variables ( might be more in future for other categories of words-> left that now for future)
    setIfSingular();
}

void AlgorythmWord::setIfSingular()
{
    //sets randomly if word is singular or plurar
    int x = rand()%2;

    if (x == 0){
        isSingular = true;
    }
    else isSingular = false;
}

void AlgorythmWord::setWordSQLTable(QString table)
{
    //sets SQL table to pick from
    wordTable = table;
}

void AlgorythmWord::setWordSQLColumn()
{
    //sets SQL column to pick from depending on if word is singular or plurar
    if (isSingular == true)
    {
        wordColumn = "singularGerman";
    }
    else wordColumn = "plurarGerman";
}

void AlgorythmWord::setWordSQLRow()
{
    //sets SQL row index to pick from
    wordIndex = rand()%30;
}

void AlgorythmWord::setWordQuery()
{
    //sets finall word query
    querySQLWord = "SELECT " + wordColumn + " FROM " + wordTable;
}

void AlgorythmWord::defineTranslation()
{
    //steps to define translation
    setWordTranslationSQLColumn();
    setWordTranslationQuery();
}

void AlgorythmWord::setWordTranslationSQLColumn()
{
    //sets SQL column of translation depengin if word is singular or plurar
    if (isSingular == true)
    {
        wordTranslationColumn = "singularEnglish";
    }
    else wordTranslationColumn = "plurarEnglish";
}

void AlgorythmWord::setWordTranslationQuery()
{
    //sets finall translation query
    querySQLWordTranslation = "SELECT " + wordTranslationColumn + " FROM " + wordTable;
}

void AlgorythmWord::defineGender()
{
    //steps to define gender of a word ( masculine/feminine/neutral) - not sure, if i'll use that-> for later to consider
    setGenderSQLColumn();
    setGenderSQLQuery();
}

void AlgorythmWord::setGenderSQLColumn()
{
    //sets SQL column for picking gender or no column if is plurar ( for plurar, always feminine in german)
    if (isSingular == true){
        genderColumn = "genderSingular";
    }
    else genderColumn = "none";
}

void AlgorythmWord::setGenderSQLQuery()
{
    //sets finall gender query
    if (isSingular == true)
    {
        querySQLGender = "SELECT " + genderColumn + " FROM " + wordTable;
    }
    else querySQLGender = "PLURAR_IS_FEMININE";
}

//GETTERS

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
