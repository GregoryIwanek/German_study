#ifndef SENTENCE
#define SENTENCE
#include "sentencedata.h"

class Sentence{

public:
    Sentence(QString sectionToPickFor, QString categoryOfWords);

    SentenceData sentenceData;
    SentenceData *sentenceDataPointer;

    void setSentenceChecked(bool isChecked);

    bool getIfSentenceChecked();

private:
    bool checked = false;
    //if we define words as to FlashCard section or not;
    bool groupOfWordsDefined = false;
};

#endif // SENTENCE

