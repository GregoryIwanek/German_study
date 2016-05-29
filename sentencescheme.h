#ifndef SENTENCESCHEME
#define SENTENCESCHEME
#include <QObject>
#include <QString>
#include <QList>
#include "algorythmnoun.h"
#include "algorythmverb.h"
#include "algorythmperson.h"
#include "algorythmseparator.h"

class SentenceScheme:public QObject {
    Q_OBJECT
public:
    SentenceScheme();
    void setData();
    void setDefineExtraWords();
    void setExtraWords();
    void setVariables();
    int getNumberOfExtraWords();
    void setConnections();

    void setTypeOfSentence(bool complexSentenceAllowed);
    void setDeclarativeSentence();
    void setNegativeSentence();
    void setInterrogativeSentence();
    void setComplexSentence();

    void setPersonAlgorythm();
    void setVerbAlgorythm();
    void setNounAlgorythm();
    void setSeparatorAlgorythm();
    void setAlgorythm(QString queryWord = NULL, QString queryTranslation = NULL, int index = 0, int indexTranslation = -1);

    void setQuerySQL(QString columnWord, QString columnTranslation);
    void incrementNumberOfExtraWords();
    QList<QString> getQuerySQLList(bool returnQuerySQLList);
    void setIndex(int indexWord, int indexTranslation = -1);
    QList<int> getIndexList(bool returnIndexList);
    void increaseCount();
    int getNumberOfWords();
public slots:
    void setCorrespondingSubjectSlot(int personIndex);
signals:
private:
    QList<QString> querySQLList;
    QList<QString> querySQLTranslationList;
    QList<int> indexTranslationList;
    QList<int> indexList;
    int numberOfSubsentenceses;
    int numberOfExtraWords = 0;
    bool addingExtraWords = false;
    int count;
    QString typeOfSentence;
    int correspondingSubjectPerson=8;

    AlgorythmPerson *algorythmPerson;
    AlgorythmVerb *algorythmVerb;
    AlgorythmNoun *algorythmNoun;
    AlgorythmSeparator *algorythmSeparator;
};

#endif // SENTENCESCHEME

