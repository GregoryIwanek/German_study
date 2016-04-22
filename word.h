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

    void defineInstance(QGraphicsItem *parent, QString text, QFont font, QString myQuery, int wordIndex);
    void defineInstance(QGraphicsItem *parent, QString text, QFont font, QString myQuery, QString subject);
    void setText(QString text);
    void setWordFont(QFont font);
    void setVariables();
    void setWidthOfText();
    void setHeightOfText();
    void setRoleInSentence(QString role);
    void pickWordFromSQL(QString myQuery, int index =0);
    void saveWordToSQL(QString role);
    int getWidthOfText();
    int getHeightOfText();
    void setIfPickedToRandomListOfWords(bool isPicked);
    bool getIfPickedToRandomListOfWords();
    QString getText();

private:
    QString word;
    QString roleInSentence;
    QSqlQuery query;
    bool pickedToRandomListOfWords = false;
    int widthOfText = 100;
    int heightOfText = 40;
};

#endif // WORD
