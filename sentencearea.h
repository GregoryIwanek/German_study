#ifndef SENTENCEAREA
#define SENTENCEAREA
#include <QObject>
#include <QGraphicsRectItem>
#include <QMap>

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
    void getPositionFromSceneToVariable(QPointF position);
    void setCornersToMap();

    int getSpaceLeft();
    QPointF getWordContainerStartPosition();
    double getWidth();
    double getHeight();
    QPointF getSentenceAreaCorners(QString nameOfCorner);

private:
    double lineWidth, lineHeight;
    double width, height;
    int spaceLeft;
    int numberOfWordsIn;
    bool isFull;
    QPointF wordContainerStartPosition, positionOnScene;
    QGraphicsRectItem lineTop, lineBottom;
    QMap<QString, QPointF> sentenceAreaCorners;
};

#endif // SENTENCEAREA

