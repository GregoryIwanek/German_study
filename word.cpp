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

void Word::defineInstance(QGraphicsItem *parent, QString text, QFont font, QString myQuery, int wordIndex)
{
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery, wordIndex);
    setWordFont(font);
    setVariables();
}

void Word::defineInstance(QGraphicsItem *parent, QString text, QFont font, QString myQuery, QString subject)
{
    setParentItem(parent);
    setRoleInSentence(myQuery);
    pickWordFromSQL(myQuery);
    setWordFont(font);
    setVariables();
}

void Word::setText(QString text){
    word = text;
    setPlainText(text);
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

void Word::pickWordFromSQL(QString myQuery, int index)
{
    query.exec(myQuery);
    while (query.seek(index)) {
        setText(query.value(0).toString());
        qDebug()<<query.value(0).toString();
        break;
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

QString Word::getText()
{
    return word;
}
