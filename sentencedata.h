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
    QList<Word *> getListOfWords();

private:
    QList<Word*> listOfWords;
    SentenceScheme sentenceScheme;

    QString subject;//ich, du, er, sie, es, wir, ihr, Sie/sie //subject isn't always printed!
    QString verb;//correct ending depending on subject
    QString preposition;//with, above etc.
    QString adverb;//this, that, very etc.
    QString noun;
    QString adjective;
    QString conjunction;//and, or, nor, for etc.
    int levelOfAdjective;//good, better, the best etc.
};

#endif // SENTENCEDATA

