#ifndef SENTENCESCHEME
#define SENTENCESCHEME

#include "sentencedata.h"
#include <QString>

class SentenceScheme {

public:
    SentenceScheme();

private:


    QString complexSentence;
    QString negativeSentence;
    QString declarativeSentence;
    QString interrogativeSentence;
    QString restOfSentence;

};


#endif // SENTENCESCHEME

