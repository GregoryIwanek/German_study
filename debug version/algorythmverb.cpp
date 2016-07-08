#include "algorythmverb.h"
#include <stdlib.h>

AlgorythmVerb::AlgorythmVerb(int subjectIndex)
{
    //sets verb depending on subject ( noun)
    setIndexBySubjectIndex(subjectIndex);
    setData();
}

void AlgorythmVerb::setData()
{
    //steps to define verb and translation
    setVariables();
    defineVerb();
    defineTranslation();
}

void AlgorythmVerb::setVariables()
{

}

void AlgorythmVerb::defineVerb()
{
    //steps to define verb
    setVerbSQLTable();
    setVerbSQLColumn();
    setVerbRowIndex(28);
    setVerbQuery();
}

void AlgorythmVerb::setVerbSQLTable()
{
    //sets SQL table to pick from
    verbTable = "VERB_ANIMALS";
}

void AlgorythmVerb::setVerbSQLColumn()
{
    //sets SQL column to pick from depending on subject ( I, you, he, they etc.)
    //sets isVerbThirdPerson true when we need english translation with "s" at the end ( for third person)
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
    //sets SQL row index to pick from
    verbIndex = rand()%indexMax;
}

void AlgorythmVerb::setVerbQuery()
{
    //sets final verb query
    querySQLVerb = "SELECT " + verbColumn + " FROM " + verbTable;
}

void AlgorythmVerb::defineTranslation()
{
    //steps to define translation
    setVerbTranslationSQLColumn();
    setVerbTranslationQuery();
}

void AlgorythmVerb::setVerbTranslationSQLColumn()
{
    //sets SQL column of translation to pick from, depends on if it's third person or not
    if (isVerbThirdPerson == true){
        verbTranslationColumn = "translation3pr";
    }
    else {
        verbTranslationColumn = "translation";
    }
}

void AlgorythmVerb::setVerbTranslationQuery()
{
    //sets finall translation query
    querySQLVerbTranslation = "SELECT " + verbTranslationColumn + " FROM " + verbTable;
}

//GETTERS

QString AlgorythmVerb::getQuery()
{
    return querySQLVerb;
}

QString AlgorythmVerb::getQueryTranslation()
{
    return querySQLVerbTranslation;
}

int AlgorythmVerb::getVerbIndex()
{
    return verbIndex;
}

void AlgorythmVerb::setIndexBySubjectIndex(int index)
{
    correspondingSubjectIndex = index;
}
