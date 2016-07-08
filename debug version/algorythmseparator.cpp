#include "algorythmseparator.h"
#include <QDebug>

AlgorythmSeparator::AlgorythmSeparator()
{
    setData();
}

void AlgorythmSeparator::setData()
{
    //steps to define separator and translation( and, or, etc.)
    defineSeparator();
    defineTranslation();
}

void AlgorythmSeparator::defineSeparator()
{
    //steps to define separator
    setSeparatorSQLTable();
    setSeparatorSQLColumn();
    setSeparatorSQLRowIndex(5);
    setSeparatorQuery();
}

void AlgorythmSeparator::setSeparatorSQLTable()
{
    //sets SQL table to pick from
    separatorTable = "SEPARATOR";
}

void AlgorythmSeparator::setSeparatorSQLColumn()
{
    //sets SQL column to pick from
    separatorColumn = "word";
}

void AlgorythmSeparator::setSeparatorSQLRowIndex(int indexMax)
{
    //sets SQL row index to pick from
    separatorIndex = rand()%indexMax;
}

void AlgorythmSeparator::setSeparatorQuery()
{
    //sets final query of separator
    querySQLSeparator = "SELECT " + separatorColumn + " FROM " + separatorTable;
}

void AlgorythmSeparator::defineTranslation()
{
    //stes to define translation of separator
    setSeparatorTranslationSQLColumn();
    setSeparatorTranslationQuery();
}

void AlgorythmSeparator::setSeparatorTranslationSQLColumn()
{
    //sets column SQL to pick from
    separatorTranslationColumn = "translation";
}

void AlgorythmSeparator::setSeparatorTranslationQuery()
{
    //sets finall query of translation
    querySQLSeparatorTranslation = "SELECT " + separatorTranslationColumn + " FROM " + separatorTable;
}

//GETTERS

QString AlgorythmSeparator::getQuery()
{
    return querySQLSeparator;
}

QString AlgorythmSeparator::getQueryTranslation()
{
    return querySQLSeparatorTranslation;
}

int AlgorythmSeparator::getSeparatorIndex()
{
    return separatorIndex;
}

