#ifndef WORD
#define WORD
#include <QString>
#include <QGraphicsTextItem>
#include <QtSql/QSql>
#include <QDebug>
#include <QFileInfo>

class Word:public QGraphicsTextItem{
    Q_OBJECT
public:
    Word(QGraphicsItem *parent =0);

    void defineInstance(QGraphicsItem *parent, QString text, QFont font);
    void setText(QString text);
    void setWordFont(QFont font);
    void setVariables();
    void setWidthOfText();
    void setHeightOfText();
    void pickWordFromSQL();
    void saveWordToSQL();
    double getWidthOfText();
    double getHeightOfText();

private:
    QString word;
    QString roleInSentence;
    double widthOfText;
    double heightOfText;
};

#endif // WORD
