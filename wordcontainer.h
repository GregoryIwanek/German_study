#ifndef WORDCONTAINER
#define WORDCONTAINER
#include "apperiance.h"
#include "word.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QTimer>

extern Apperiance *apperiance;

class WordContainer:public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    WordContainer(Word *myWord);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void setTimersAndConnections();

    void setMyFlags();
    void setSize(int width, int height);
    void setColor(QBrush brush);
    void setText(Word *myWord);
    void setTextPosition();
    void setSizeOfRect();
    void setStartPosition(QPointF point);
    void setIsOnSentenceArea(bool isChecked);
    void setPos(const QPointF & pos);
    void setNextContainerPositionInSentenceArea(QPointF *point);
    void setIndexOnSentenceArea(int index);

    int getWidthOfRect();
    int getHeightOfRect();
    QPointF getStartPosition();
    QString getTextFromWord();
    bool getIsOnSentenceArea();
    int getIndexOnSentenceArea();
public slots:
    void sendToSentenceArea(QPointF point);
    void move();
    void checkIfStopMovement();
    void setDistanceAndDirectionToMoveToArea();
    void setDistanceAndDirectionToMoveFromArea();
    void sendToStartArea(QPointF point);
signals:
    void clicked(WordContainer *wordContainer);
    void stopped(WordContainer *wordContainer, bool isWordContainerMoved);
private:
    Word *text,word;
    QTimer *timer;
    int widthOfRect;
    int heightOfRect;
    int widthOfText, heightOfText;
    int angleToMove;
    int indexOnSentenceArea = NULL;
    QPointF startPosition, *nextContainerPositionInSentenceArea;
    bool isOnSentenceArea = false;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // WORDCONTAINER
