#include "sentence.h"
#include <QDebug>

Sentence::Sentence(QString sectionToPickFor, QString categoryOfWords)
{
    //constructor called for GSSection and FCSection, with infor about section and category of words ( if it's FCSection)
    sentenceDataPointer = new SentenceData(sectionToPickFor, categoryOfWords);
}

void Sentence::setSentenceChecked(bool isChecked)
{
    //for GSSection-> sets sentence as checked, so we block possibility to click button check again
    checked = isChecked;
}

//GETTERS

bool Sentence::getIfSentenceChecked()
{
    return checked;
}

