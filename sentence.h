#ifndef SENTENCE
#define SENTENCE
#include "sentencedata.h"

class Sentence{

public:
    Sentence();

    SentenceData sentenceData;

    void setSentenceChecked(bool isChecked);
    bool getIfSentenceChecked();

private:
    bool checked = false;
};

#endif // SENTENCE

