#ifndef ALGORYTHMSEPARATOR_H
#define ALGORYTHMSEPARATOR_H
#include <QObject>

class AlgorythmSeparator{

public:
    AlgorythmSeparator();

    void setData();
    void defineSeparator();
    void setSeparatorSQLTable();
    void setSeparatorSQLColumn();
    void setSeparatorSQLRowIndex(int indexMax);
    void setSeparatorQuery();
    void defineTranslation();
    void setSeparatorTranslationSQLColumn();
    void setSeparatorTranslationQuery();

    QString getQuery();
    QString getQueryTranslation();
    int getSeparatorIndex();

private:
    QString separatorTable;
    QString separatorColumn, separatorTranslationColumn;
    QString querySQLSeparator, querySQLSeparatorTranslation;
    int separatorIndex;
};

#endif // ALGORYTHMSEPARATOR_H
