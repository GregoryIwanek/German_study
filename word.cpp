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
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery, wordIndex, false);
    pickWordFromSQL(translationQuery, translationIndex, true);
    setWordFont(font);
}

void Word::defineInstance(QGraphicsItem *parent, QFont font, QString myQuery)
{
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery);
    setWordFont(font);
}

void Word::setText(QString text, bool isItTranslation){

    if (isItTranslation == false){
        word = text;
        setPlainText(text);
    }
    else
    {
        translation = text;
        setPlainText(translation);
    }

    setVariablesSizeOfText();
}

void Word::setWordFont(QFont font){
    setFont(font);
    setVariablesSizeOfText();
}

void Word::setVariablesSizeOfText(){
    setWidthOfText();
    setHeightOfText();
}

void Word::setWidthOfText()
{
    if (this->boundingRect().width() > 0){
        widthOfText = this->boundingRect().width();
    }
    else widthOfText = 100;
}

void Word::setHeightOfText()
{
    if (this->boundingRect().height() > 0){
        heightOfText = this->boundingRect().height();
    }
    else heightOfText = 40;
}

void Word::setRoleInSentence(QString role)
{
    roleInSentence = role;
}

void Word::pickWordFromSQL(QString myQuery, int index, bool isItTranslation)
{
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

}

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
