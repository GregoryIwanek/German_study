#include "algorythmperson.h"
#include <stdlib.h>

AlgorythmPerson::AlgorythmPerson()
{

}

void AlgorythmPerson::setData()
{
    definePerson();
    defineTranslation();
}

void AlgorythmPerson::definePerson()
{
    setPersonSQLTable();
    setPersonSQLColumn();
    setPersonSQLRowIndex(8);
    setPersonQuery();
}

void AlgorythmPerson::setPersonSQLTable()
{
    personTable = "DIRECT_SUBJECT";
}

void AlgorythmPerson::setPersonSQLColumn()
{
    personColumn = "word";
}

void AlgorythmPerson::setPersonSQLRowIndex(int indexMax)
{
    personIndex = rand()%indexMax;
}

void AlgorythmPerson::setPersonQuery()
{
    querySQLPerson = "SELECT " + personColumn + " FROM " + personTable;
}

void AlgorythmPerson::defineTranslation()
{
    setPersonTranslationSQLColumn();
    setPersonTranslationQuery();
}

void AlgorythmPerson::setPersonTranslationSQLColumn()
{
    personTranslationColumn = "translation";
}

void AlgorythmPerson::setPersonTranslationQuery()
{
    querySQLPersonTranslation = "SELECT " + personTranslationColumn + " FROM " + personTable;
}

QString AlgorythmPerson::getQueries()
{
    return querySQLPerson, querySQLPersonTranslation;
}

int AlgorythmPerson::getPersonIndex()
{
    return personIndex, personIndex;
}
