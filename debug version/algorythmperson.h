#ifndef ALGORYTHMPERSON_H
#define ALGORYTHMPERSON_H
#include <QObject>

class AlgorythmPerson:public QObject{
    Q_OBJECT
public:
    AlgorythmPerson();

    void setData();
    void definePerson();
    void setPersonSQLTable();
    void setPersonSQLColumn();
    void setPersonSQLRowIndex(int indexMax);
    void setPersonQuery();
    void defineTranslation();
    void setPersonTranslationSQLColumn();
    void setPersonTranslationQuery();

    QString getQuery();
    QString getQueryTranslation();
    int getPersonIndex();

signals:
    void subjectType(int subjectIndex); // emits subject's index in SQL table, then correct version of VERB is picked by this subject

private:
    QString personTable;
    QString personColumn, personTranslationColumn;
    QString querySQLPerson, querySQLPersonTranslation;
    int personIndex;
};

#endif // ALGORYTHMPERSON_H
