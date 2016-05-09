#include "algorythmverb.h"
#include <stdlib.h>

AlgorythmVerb::AlgorythmVerb()
{

}

void AlgorythmVerb::setData()
{
    setVariables();
    defineVerb();
    defineTranslation();
}

void AlgorythmVerb::setVariables()
{

}

void AlgorythmVerb::defineVerb()
{
    setVerbSQLTable();
    setVerbSQLColumn();
    setVerbRowIndex(28);
    setVerbQuery();
}

void AlgorythmVerb::setVerbSQLTable()
{
    verbTable = "VERBS_ANIMALS";
}

void AlgorythmVerb::setVerbSQLColumn()
{
    switch (correspondingSubjectIndex) {
    case 0: verbColumn = "ich";
        break;
    case 1: verbColumn = "du";
        break;
    case 2: verbColumn = "er";
        isVerbThirdPerson = true;
        break;
    case 3: verbColumn = "sie";
        isVerbThirdPerson = true;
        break;
    case 4: verbColumn = "es";
        isVerbThirdPerson = true;
        break;
    case 5: verbColumn = "wir";
        break;
    case 6: verbColumn = "ihr";
        break;
    case 7: verbColumn = "sie_3";
        break;
    default:
        break;
    }
}

void AlgorythmVerb::setVerbRowIndex(int indexMax)
{
    verbIndex = rand()%indexMax;
}

void AlgorythmVerb::setVerbQuery()
{
    querySQLVerb = "SELECT " + verbColumn + " FROM " + verbTable;
}

void AlgorythmVerb::defineTranslation()
{
    setVerbTranslationSQLColumn();
    setVerbTranslationQuery();
}

void AlgorythmVerb::setVerbTranslationSQLColumn()
{
    if (isVerbThirdPerson == true){
        verbTranslationColumn = "translation3pr";
    }
    else {
        verbTranslationColumn = "translation";
    }
}

void AlgorythmVerb::setVerbTranslationQuery()
{
    querySQLVerbTranslation = "SELECT " + verbTranslationColumn + " FROM " + verbTable;
}

QString AlgorythmVerb::getQueries()
{
    return querySQLVerb, querySQLVerbTranslation;
}

int AlgorythmVerb::getVerbIndex()
{
    return verbIndex, verbIndex;
}

void AlgorythmVerb::setIndexBySubjectIndex(int index)
{
    correspondingSubjectIndex = index;
}
