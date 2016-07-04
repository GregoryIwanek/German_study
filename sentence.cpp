#include "sentence.h"
#include <QDebug>

Sentence::Sentence()
{

}

Sentence::Sentence(QString sectionToPickFor, QString categoryOfWords)
{
    sentenceDataPointer = new SentenceData(sectionToPickFor, categoryOfWords);
}

void Sentence::setSentenceChecked(bool isChecked)
{
    checked = isChecked;
}

bool Sentence::getIfSentenceChecked()
{
    return checked;
}

