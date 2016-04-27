#include "sentence.h"

Sentence::Sentence()
{

}

void Sentence::setSentenceChecked(bool isChecked)
{
    checked = isChecked;
}

bool Sentence::getIfSentenceChecked()
{
    return checked;
}
