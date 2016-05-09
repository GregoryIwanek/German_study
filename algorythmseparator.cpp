#include "algorythmseparator.h"
#include <QDebug>

AlgorythmSeparator::AlgorythmSeparator()
{
    setData();
}

void AlgorythmSeparator::setData()
{
    defineSeparator();
    defineTranslation();
}

void AlgorythmSeparator::defineSeparator()
{
    setSeparatorSQLTable();
    setSeparatorSQLColumn();
    setSeparatorSQLRowIndex(5);
    setSeparatorQuery();
}

void AlgorythmSeparator::setSeparatorSQLTable()
{
    separatorTable = "SEPARATOR";
}

void AlgorythmSeparator::setSeparatorSQLColumn()
{
    separatorColumn = "word";
}

void AlgorythmSeparator::setSeparatorSQLRowIndex(int indexMax)
{
    separatorIndex = rand()%indexMax;
}

void AlgorythmSeparator::setSeparatorQuery()
{
    querySQLSeparator = "SELECT " + separatorColumn + " FROM " + separatorTable;
}

void AlgorythmSeparator::defineTranslation()
{
    setSeparatorTranslationSQLColumn();
    setSeparatorTranslationQuery();
}

void AlgorythmSeparator::setSeparatorTranslationSQLColumn()
{
    separatorTranslationColumn = "translation";
}

void AlgorythmSeparator::setSeparatorTranslationQuery()
{
    querySQLSeparatorTranslation = "SELECT " + separatorTranslationColumn + " FROM " + separatorTable;
}

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

