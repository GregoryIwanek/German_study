#ifndef SENTENCEDATA
#define SENTENCEDATA
#include <QString>
#include "word.h"
#include "sentencescheme.h"

class SentenceData{

public:
    SentenceData();

    void setSentenceScheme();
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
    int indexToPick, numberOfPickedWordsToRandomList=0;
};

#endif // SENTENCEDATA

