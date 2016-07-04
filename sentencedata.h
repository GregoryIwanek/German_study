#ifndef SENTENCEDATA
#define SENTENCEDATA
#include <QString>
#include "word.h"
#include "sentencescheme.h"

class SentenceData{

public:
    SentenceData();
    SentenceData(const SentenceData &sentenceData); //copy constructor- beacouse of errors
    SentenceData(QString sectionToPickFor, QString categoryOfWords);

    void setSentenceScheme(QString sectionToPickFor, QString categoryOfWords);
    void setSchemeToWords();
    void setRandomOrderList();
    void setSentenceAndTranslation();
    QList<Word *> getListOfWords();
    QList<Word *> getListOfWordsInRandomOrder();
    QList<QString> getCorrectSentence();
    QString getCorrectTranslationString();
    QString getCorrectSentenceString();

private:
    QList<Word*> listOfWords;
    QList<Word*> listOfWordsRandomOrder;
    QList<QString> listCorrectSentence;
    QString correctTranslationString, correctSentenceString;
    SentenceScheme sentenceScheme;
    SentenceScheme *sentenceSchemePointer;
    int indexToPick, numberOfPickedWordsToRandomList=0;
};

#endif // SENTENCEDATA

