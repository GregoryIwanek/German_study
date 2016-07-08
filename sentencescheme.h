#ifndef SENTENCESCHEME
#define SENTENCESCHEME
#include <QObject>
#include <QString>
#include <QList>
#include "algorythmnoun.h"
#include "algorythmverb.h"
#include "algorythmperson.h"
#include "algorythmseparator.h"
#include "algorythmword.h"

class SentenceScheme:public QObject {
    Q_OBJECT
public:
    SentenceScheme();
    SentenceScheme(QString sectionToPickFor, QString categoryOfWords);

    void setBasicData(QString sectionToPickFor, QString categoryOfWords);
    void setDataForGuessSentence();
    void setDataForFlashCard(QString categoryOfWords);
    void setDefineExtraWords();
    void setExtraWords();
    void setVariables();
    void setConnections();

    void setTypeOfSentence(bool complexSentenceAllowed = true);
    void setDeclarativeSentence();
    void setNegativeSentence();
    void setInterrogativeSentence();
    void setExpression();
    void setComplexSentence();
    void setFlashCardList(QString categoryOfWords);
    void setRemoveFromListsIfSameIndex();

    void setPersonAlgorythm();
    void setVerbAlgorythm();
    void setNounAlgorythm();
    void setNounAlgorythmAsSubject();
    void setSeparatorAlgorythm();
    void setWordAlgorythm(QString categoryOfWords);
    void setAlgorythm(QString queryWord = NULL, QString queryTranslation = NULL, int index = 0, int indexTranslation = -1);
    void setGender(QString queryGender);
    void checkIfIndexAlreadyPicked();

    void setQuerySQL(QString columnWord, QString columnTranslation);
    void incrementNumberOfExtraWords();
    QList<QString> getQuerySQLList(bool returnQuerySQLList);
    QList<QString> getQuerySQLGenderList();
    void setIndex(int indexWord, int indexTranslation = -1);
    QList<int> getIndexList(bool returnIndexList);
    void increaseCount();
    int getNumberOfWords();
    int getNumberOfExtraWords();
public slots:
    void setCorrespondingSubjectSlot(int personIndex);
signals:
private:
    QList<QString> querySQLList;
    QList<QString> querySQLTranslationList;
    QList<QString> querySQLGenderList;
    QList<int> indexTranslationList;
    QList<int> indexList;
    int numberOfSubsentenceses = 0;
    int numberOfExtraWords = 0;
    int count = 0;
    int numberFCWordsToPick = 16;
    bool addingExtraWords = false;
    QString typeOfSentence;
    int correspondingSubjectPerson=8;

    bool pickForFCSection;
    bool isIndexSQLAlreadyChosen = false;

    AlgorythmPerson *algorythmPerson;
    AlgorythmVerb *algorythmVerb;
    AlgorythmNoun *algorythmNoun;
    AlgorythmSeparator *algorythmSeparator;
    AlgorythmWord *algorythmWord;
};

#endif // SENTENCESCHEME

