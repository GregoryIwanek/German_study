#ifndef GUESSSENTENCESECTION
#define GUESSSENTENCESECTION
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLineEdit>
#include "wordcontainer.h"
#include "sentence.h"
#include "sentencearea.h"
#include "customscene.h"
class GuessSentenceSection:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    GuessSentenceSection();

    void setSceneFromMainWindow(CustomScene *myScene);

    void setMenu();
    void setButtons();
    void setPoints();
    void setBorderRect();

    void setWordContainers();
    void setColumn();
    void setRow(int y);
    void setSentenceAreas();
    void setInputComponents();
    void setSignNextWordContainerPositionToContainers();
    void setVariables();
    void checkWordContainerCollision(QPointF startPointOfChecked);
    void setIndexOfWordContainerOnSentenceArea(WordContainer *wordContainer);
    void updateIndexOfWordContainersOnSentenceArea(int index);
    void updateIndexOfSentenceInputByUserList(WordContainer *wordContainer);

    QPointF getClosestGridPoint(QPointF point);

public slots:
    void sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer);
    void setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved);
    void updateSentence(WordContainer *wordContainer);
    void setSession();
    void checkSentence();
    void back();
    void clearSentence();
    void setGuessSentenceSectionVisible();
signals:
private:
    bool isWordContainerMoved = false;
    int endOfWordContainer = 0;
    int indexOfWordContainerOnSentenceArea = 0;
    CustomScene *scene;
    QList<SentenceArea*> sentenceAreaList;
    QList<WordContainer*> wordContainerList;
    QList<Sentence*> sentenceList;
    QList<QString> sentenceInputByUserList;
    QGraphicsTextItem *sentence;
    QLineEdit *lineEdit;
    QPointF nextWordContainerPosition,*nextWordContainerPositionPointer;
    QTime *systemTime;
};

#endif // GUESSSENTENCESECTION
