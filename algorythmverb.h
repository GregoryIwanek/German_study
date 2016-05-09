#ifndef ALGORYTHMVERB_H
#define ALGORYTHMVERB_H
#include <QObject>

class AlgorythmVerb:public QObject{
    Q_OBJECT
public:
    AlgorythmVerb();
    AlgorythmVerb(int subjectIndex);

    void setData();
    void setVariables();
    void defineVerb();
    void setVerbSQLTable();
    void setVerbSQLColumn();
    void setVerbRowIndex(int indexMax);
    void setVerbQuery();
    void defineTranslation();
    void setVerbTranslationSQLColumn();
    void setVerbTranslationQuery();

    QString getQuery();
    QString getQueryTranslation();
    int getVerbIndex();
public slots:
    void setIndexBySubjectIndex(int index);
signals:
private:
    QString querySQLVerb, querySQLVerbTranslation;
    QString verbTable;
    QString verbColumn, verbTranslationColumn;
    bool isVerbThirdPerson = false;
    int correspondingSubjectIndex = 0;
    int verbIndex;
};

#endif // ALGORYTHMVERB_H
