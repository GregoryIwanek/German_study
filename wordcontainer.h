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
    WordContainer(Word *myWord);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void setMyFlags();
    void setSize(int width, int height);
    void setColor(QBrush brush);
    void setText(Word *myWord);
    void setTextPosition();
    void setSizeOfRect();
    void setStartPosition(QPointF point);
    void setIsMoved(bool isChecked);
    void setPos(const QPointF & pos);

    int getWidthOfRect();
    int getHeightOfRect();
    QPointF getStartPosition();
    bool getIsMoved();
public slots:
    void sendToSentenceArea(QPointF point);
    void sendToStartArea(QPointF point);

signals:
    void clicked(WordContainer *wordContainer);
private:
    Word *text,word;
    int widthOfRect;
    int heightOfRect;
    int widthOfText, heightOfText;
    QPointF startPosition;
    bool isMoved = false;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // WORDCONTAINER
