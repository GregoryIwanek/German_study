#ifndef SENTENCESCHEME
#define SENTENCESCHEME

#include "sentencedata.h"
#include <QString>

class SentenceScheme {

public:
    SentenceScheme();

    void setTypeOfSentence();
    void setHowManySubsentenceses();

private:
    int numberOfSubsentenceses;
    QString typeOfSentence;
    QString complexSentence;
    QString negativeSentence;
    QString declarativeSentence;
    QString interrogativeSentence;
    QString restOfSentence;

};


#endif // SENTENCESCHEME

