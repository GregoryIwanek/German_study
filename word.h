#ifndef WORD
#define WORD
#include <QString>
#include <QGraphicsTextItem>

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
    double getWidthOfText();
    double getHeightOfText();

private:
    double widthOfText;
    double heightOfText;
};

#endif // WORD
