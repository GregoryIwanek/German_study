#ifndef WORDCONTAINER
#define WORDCONTAINER
#include "apperiance.h"
#include "word.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

extern Apperiance *apperiance;

class WordContainer:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WordContainer();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setSize(int width, int height);
    void setColor(QBrush brush);
    void setText();
    void setTextPosition();
    void setSizeOfRect();
    void setStartPosition(QPointF point);
    void setIsMoved(bool isChecked);

    double getWidthOfRect();
    double getHeightOfRect();
    QPointF getStartPosition();
    bool getIsMoved();

public slots:
    void sendToSentenceArea(QPointF point);
    void sendToStartArea(QPointF point);

signals:
    void clicked(WordContainer *wordContainer);
private:
    Word text;
    //QGraphicsTextItem *text;
    double widthOfRect;
    double heightOfRect;
    QPointF startPosition;
    bool isMoved = false;
};

#endif // WORDCONTAINER

