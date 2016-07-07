#ifndef WORD
#define WORD
#include <QString>
#include <QGraphicsTextItem>
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>

class Word:public QGraphicsTextItem{

public:
    Word();
    Word(const Word &copyWord);

    void defineInstance(QGraphicsItem *parent, QFont font, QString myQuery, int wordIndex,
                        QString translationQuery, int translationIndex);
    void setText(QString text, bool isItTranslation);
    void setWordFont(QFont font);
    void setVariablesSizeOfText();
    void setWidthOfText();
    void setHeightOfText();
    void setRoleInSentence(QString role);
    void pickWordFromSQL(QString myQuery, int index =0, bool isItTranslation =false);
    void pickExtraInfoFromSQL(QString extraQuery, int index = 0);
    void saveWordToSQL();
    double getWidthOfText();
    double getHeightOfText();
    void setIfPickedToRandomListOfWords(bool isPicked);
    bool getIfPickedToRandomListOfWords();
    void setIfIsTranslation(bool isItTranslation);
    bool getIfIsTranslation();
    QString getText(bool returnTranslation);

private:
    QString word;
    QString translation;
    QString roleInSentence;
    QString extraInformation;
    QSqlQuery query;
    bool pickedToRandomListOfWords = false;
    bool isTranslation = false;
    double widthOfText = 100;
    double heightOfText = 40;
};

#endif // WORD
