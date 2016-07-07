#include "algorythmperson.h"
#include <stdlib.h>

AlgorythmPerson::AlgorythmPerson()
{
    setData();
}

void AlgorythmPerson::setData()
{
    //series of steps to define person and translation
    definePerson();
    defineTranslation();
}

void AlgorythmPerson::definePerson()
{
    //steps to define person (subject: I, you, he etc.)
    setPersonSQLTable();
    setPersonSQLColumn();
    setPersonSQLRowIndex(8);
    setPersonQuery();
}

void AlgorythmPerson::setPersonSQLTable()
{
    //sets table SQL to pick from
    personTable = "DIRECT_SUBJECT";
}

void AlgorythmPerson::setPersonSQLColumn()
{
    //sets column SQL to pick from
    personColumn = "word";
}

void AlgorythmPerson::setPersonSQLRowIndex(int indexMax)
{
    //sets row index in SQL to pick from and emit signal for later use by definition of VERB ( verb depends on subject)
    personIndex = rand()%indexMax;
    emit subjectType(personIndex);
}

void AlgorythmPerson::setPersonQuery()
{
    //sets final query for person
    querySQLPerson = "SELECT " + personColumn + " FROM " + personTable;
}

void AlgorythmPerson::defineTranslation()
{
    //steps to define translation
    setPersonTranslationSQLColumn();
    setPersonTranslationQuery();
}

void AlgorythmPerson::setPersonTranslationSQLColumn()
{
    //sets column SQL for translation to pick from
    personTranslationColumn = "translation";
}

void AlgorythmPerson::setPersonTranslationQuery()
{
    //sets final translation query
    querySQLPersonTranslation = "SELECT " + personTranslationColumn + " FROM " + personTable;
}

//GETTERS

QString AlgorythmPerson::getQuery()
{
    return querySQLPerson;
}

QString AlgorythmPerson::getQueryTranslation()
{
    return querySQLPersonTranslation;
}

int AlgorythmPerson::getPersonIndex()
{
    return personIndex;
}
