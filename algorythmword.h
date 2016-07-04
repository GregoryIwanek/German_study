#ifndef ALGORYTHMWORD_H
#define ALGORYTHMWORD_H
#include <QObject>

class AlgorythmWord:public QObject{
    Q_OBJECT
public:
    AlgorythmWord();

    void setData();
    void defineWord();
    void setWordSQLTable();
    void setWordSQLColumn();
    void setWordSQLRow();
    void setWordQuery();
    void defineTranslation();
    void setWordTranslationSQLColumn();
    void setWordTranslationQuery();

    QString getQuery();
    QString getQueryTranslation();
    int getWordIndex();

signals:

private:
    QString wordTable;
    QString wordColumn, wordTranslationColumn;
    QString querySQLWord, querySQLWordTranslation;
    int wordIndex;
};

#endif // ALGORYTHMWORD_H
