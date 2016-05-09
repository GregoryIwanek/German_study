#ifndef WORD
#define WORD
#include <QString>
#include <QGraphicsTextItem>
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>

class Word:public QGraphicsTextItem{
    Q_OBJECT
public:
    Word();
    Word(const Word &word);

    void defineInstance(QGraphicsItem *parent, QFont font, QString myQuery, int wordIndex,
                        QString translationQuery, int translationIndex);
    void defineInstance(QGraphicsItem *parent, QFont font, QString myQuery);
    void setText(QString text, bool isItTranslation);
    void setWordFont(QFont font);
    void setVariables();
    void setWidthOfText();
    void setHeightOfText();
    void setRoleInSentence(QString role);
    void pickWordFromSQL(QString myQuery, int index =0, bool isItTranslation =false);
    void saveWordToSQL(QString role);
    int getWidthOfText();
    int getHeightOfText();
    void setIfPickedToRandomListOfWords(bool isPicked);
    bool getIfPickedToRandomListOfWords();
    QString getText(bool returnTranslation);

private:
    QString word;
    QString translation;
    QString roleInSentence;
    QSqlQuery query;
    bool pickedToRandomListOfWords = false;
    int widthOfText = 100;
    int heightOfText = 40;
};

#endif // WORD
