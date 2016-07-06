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
    WordContainer(Word *myWord = NULL);
    WordContainer(int width = 0, int height = 0, Word *myWord = NULL, bool isItTranslation = false);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void setTimersAndConnections();

    void setMyFlags();
    void setSize(int width, int height);
    void setColor(QBrush brush);
    void setIfIsTranslation(bool isItTranslation);
    void setText(Word *myWord);
    void setWordFCSection(Word *myWord);
    void setTextPosition();
    void setSizeOfRect();
    void setFixedSizeOfRect(int width, int height);
    void setStartPosition(QPointF point);
    void setIsOnSentenceArea(bool isChecked);
    void setPos(const QPointF & pos);
    void setNextContainerPositionInSentenceArea(QPointF *point);
    void setIndexOnSentenceArea(int index);
    void setIsChecked(bool isItemChecked);
    void setSectionItBelongsTo(QString section);

    void sendContainerFromOrToSentenceArea();
    void switchTimers();

    double getWidthOfRect();
    double getHeightOfRect();
    QPointF getStartPosition();
    QString getTextFromWord();
    bool getIsOnSentenceArea();
    bool getIfIsChecked();
    int getIndexOnSentenceArea();
    Word *getWordPointerOfWordContainer();

    QString sectionItBelongsTo;

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
    bool isItDisplayingTranslation = false;
    bool isChecked = false;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // WORDCONTAINER
