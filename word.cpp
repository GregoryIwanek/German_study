#include "word.h"
#include "apperiance.h"
#include <QSqlQuery>
#include <QDebug>

extern Apperiance *apperiance;

Word::Word()
{

}

Word::Word(const Word &word)
{

}

void Word::defineInstance(QGraphicsItem *parent, QFont font, QString myQuery, int wordIndex,
                          QString translationQuery, int translationIndex)
{
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery, wordIndex, false);
    pickWordFromSQL(translationQuery, translationIndex, true);
    setWordFont(font);
    setVariables();
}

void Word::defineInstance(QGraphicsItem *parent, QFont font, QString myQuery)
{
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery);
    setWordFont(font);
    setVariables();
}

void Word::setText(QString text, bool isItTranslation){

    if (isItTranslation == false){
        word = text;
        setPlainText(text);
    }
    else translation = text;
}

void Word::setWordFont(QFont font){
    setFont(font);
}

void Word::setVariables(){
    setWidthOfText();
    setHeightOfText();
}

void Word::setWidthOfText()
{
    if (this->boundingRect().width()){
        widthOfText = this->boundingRect().width();
    }
    else widthOfText = 100;
}

void Word::setHeightOfText()
{
    if (this->boundingRect().height()){
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
            qDebug()<<"original querry: "<<query.value(0).toString();
            setText(query.value(0).toString(), false);
            break;
        }
    }
    else {
        query.exec(myQuery);
        while (query.seek(index)) {
            qDebug()<<"translation querry: "<<query.value(0).toString();
            setText(query.value(0).toString(), true);
            break;
        }
    }
}

void Word::saveWordToSQL(QString role)
{

}

int Word::getWidthOfText()
{
    return widthOfText;
}

int Word::getHeightOfText()
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

QString Word::getText(bool returnTranslation)
{
    if (returnTranslation == false){

        return word;
    }
    else return translation;
}
