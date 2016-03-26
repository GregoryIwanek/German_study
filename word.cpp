#include "word.h"
#include "apperiance.h"
#include <QDebug>

extern Apperiance *apperiance;

Word::Word(QGraphicsItem *parent): QGraphicsTextItem(parent)
{

}

void Word::defineInstance(QGraphicsItem *parent, QString text, QFont font){
    setParentItem(parent);
    setText(text);
    setWordFont(font);
    setVariables();
}

void Word::setText(QString text){
    roleInSentence = NULL;
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

void Word::setWidthOfText(){
    widthOfText = this->boundingRect().width();
}

void Word::setHeightOfText(){
    heightOfText = this->boundingRect().height();
}

void Word::pickWordFromSQL()
{

}

void Word::saveWordToSQL()
{

}

double Word::getWidthOfText(){
    return widthOfText;
}

double Word::getHeightOfText(){
    return heightOfText;
}


