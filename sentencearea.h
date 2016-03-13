#ifndef SENTENCEAREA
#define SENTENCEAREA
#include <QObject>
#include <QGraphicsRectItem>

class SentenceArea:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    SentenceArea();

    void setSizeOfArea();
    void setSizeOfLines();
    void setLinesPosition();
    void setBrushes();
    void setSpaceLeft();
    void setWordContainerStartPosition(QPointF position);

    int getSpaceLeft();
    QPointF getWordContainerStartPosition();

private:
    int lineWidth, lineHeight;
    int width, height;
    int spaceLeft;
    int numberOfWordsIn;
    bool isFull;
    QPointF wordContainerStartPosition;
    QGraphicsRectItem lineTop, lineBottom;
};

#endif // SENTENCEAREA

