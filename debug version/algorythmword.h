#ifndef ALGORYTHMWORD_H
#define ALGORYTHMWORD_H
#include <QObject>

class AlgorythmWord:public QObject{
    Q_OBJECT

public:
    AlgorythmWord(QString categoryOfWords);

    void setData();
    void defineWord();
    void defineVariables();
    void setIfSingular();
    void setWordSQLTable(QString table);
    void setWordSQLColumn();
    void setWordSQLRow();
    void setWordQuery();
    void defineTranslation();
    void setWordTranslationSQLColumn();
    void setWordTranslationQuery();
    void defineGender();
    void setGenderSQLColumn();
    void setGenderSQLQuery();

    QString getQuery();
    QString getQueryTranslation();
    QString getQueryGender();
    int getWordIndex();
    bool getIfIsSingular();

signals:

private:
    QString wordTable;
    QString wordColumn, wordTranslationColumn;
    QString querySQLWord, querySQLWordTranslation;
    QString genderColumn, querySQLGender;
    int wordIndex;
    bool isSingular;
};

#endif // ALGORYTHMWORD_H
