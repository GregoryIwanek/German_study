#include "sentencescheme.h"
#include <math.h>
SentenceScheme::SentenceScheme(){

}

void SentenceScheme::setTypeOfSentence()
{
    int type = 1;
    switch(type){
    case 1: typeOfSentence = "declarative";
        break;
    case 2: typeOfSentence = "negative";
        break;
    case 3: typeOfSentence = "interrogative";
        break;
    case 4: typeOfSentence = "complex";
        break;
    default: typeOfSentence = "rest";
        break;
    }
}

void SentenceScheme::setHowManySubsentenceses()
{
    numberOfSubsentenceses = rand()%5;
}

//    declarativeSentence = "subject" + " " + "verb" + " " + "rest";
//    negativeSentence = "subject" " " + "verb" + " " + "rest";
