#include "word.h"
#include "apperiance.h"
#include <QSqlQuery>
#include <QDebug>

extern Apperiance *apperiance;

Word::Word()
{

}

Word::Word(const Word &copyWord)
{
    /*copy constructor for use in FCSection ( we need copy of pointer with same values
     * to put as a word inside WordContainer (one WC with germanWord and one with englishWord, both Words store same data)*/
    word = copyWord.word;
    translation = copyWord.translation;
    roleInSentence = copyWord.roleInSentence;
    extraInformation = copyWord.extraInformation;
    query = copyWord.query;
    pickedToRandomListOfWords = copyWord.pickedToRandomListOfWords;
    widthOfText = copyWord.widthOfText;
    heightOfText = copyWord.heightOfText;
}

void Word::defineInstance(QGraphicsItem *parent, QFont font, QString myQuery, int wordIndex,
                          QString translationQuery, int translationIndex)
{
    //definition of Word instance with all data ( query, index, font etc)
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery, wordIndex, false);
    pickWordFromSQL(translationQuery, translationIndex, true);
    setWordFont(font);
}

void Word::setText(QString text, bool isItTranslation)
{
    //sets text to display depending on if Word is about to show translation or german word
    if (isItTranslation == false){
        word = text;
        setPlainText(text);
    }
    else
    {
        translation = text;
        setPlainText(translation);
    }

    //update size od text ( height, width), so later we can positon that text inside WordContainer
    setVariablesSizeOfText();
}

void Word::setWordFont(QFont font)
{
    //sets new font and update size of text
    setFont(font);
    setVariablesSizeOfText();
}

void Word::setVariablesSizeOfText()
{
    //updates size of text for later use
    setWidthOfText();
    setHeightOfText();
}

void Word::setWidthOfText()
{
    //updates width of text
    if (this->boundingRect().width() > 0){
        widthOfText = this->boundingRect().width();
    }
    else widthOfText = 100;
}

void Word::setHeightOfText()
{
    //updates height of text
    if (this->boundingRect().height() > 0){
        heightOfText = this->boundingRect().height();
    }
    else heightOfText = 40;
}

void Word::setRoleInSentence(QString role)
{
    //is that necessery???????????????????
    roleInSentence = role;
    //to investigation
}

void Word::pickWordFromSQL(QString myQuery, int index, bool isItTranslation)
{
    //connects to datebase SQL and picks word from there by using given query and if word will be translation or german word
    if (isItTranslation == false){
        query.exec(myQuery);
        while (query.seek(index)) {
            setText(query.value(0).toString(), false);
            break;
        }
    }
    else {
        query.exec(myQuery);
        while (query.seek(index)) {
            setText(query.value(0).toString(), true);
            break;
        }
    }
}

void Word::pickExtraInfoFromSQL(QString extraQuery, int index)
{
    //called from sentenceData class-> picks extra info from SQL column, such as gender, case etc.
    if (extraQuery != "PLURAR_IS_FEMININE")
    {
        query.exec(extraQuery);
        while (query.seek(index))
        {
            extraInformation = query.value(0).toString();
        }
    }
    else extraInformation = "feminine";
}

void Word::saveWordToSQL()
{
//to do later
}

//GETTERS

double Word::getWidthOfText()
{
    return widthOfText;
}

double Word::getHeightOfText()
{
    return heightOfText;
}

void Word::setIfPickedToRandomListOfWords(bool isPicked)
{
    pickedToRandomListOfWords = isPicked;
}

bool Word::getIfPickedToRandomListOfWords()
{
    return pickedToRandomListOfWords;
}

void Word::setIfIsTranslation(bool isItTranslation)
{
    isTranslation = isItTranslation;
}

bool Word::getIfIsTranslation()
{
    return isTranslation;
}

QString Word::getText(bool returnTranslation)
{
    if (returnTranslation == false){

        return word;
    }
    else return translation;
}
