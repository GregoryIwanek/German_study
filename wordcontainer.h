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

    double getWidthOfRect();
    double getHeightOfRect();
    QPointF getStartPosition();
    QString getTextFromWord();
    bool getIsOnSentenceArea();
    int getIndexOnSentenceArea();
public slots:
    void sendToSentenceArea();
    void move();
    void checkIfStopMovement();
    void setDistanceAndDirectionToMoveToArea();
    void setDistanceAndDirectionToMoveFromArea();
    void sendToStartArea();
signals:
    void clicked(WordContainer *wordContainer);
    void stopped(WordContainer *wordContainer, bool isWordContainerMoved);
    void removeGapInSpace(WordContainer *wordContainer);
private:
    Word *text,word;
    QTimer *timer;
    double widthOfRect;
    double heightOfRect;
    double widthOfText, heightOfText;
    double angleToMove;
    int indexOnSentenceArea = -1;
    QPointF startPosition, *nextContainerPositionInSentenceArea;
    bool isOnSentenceArea = false;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // WORDCONTAINER
