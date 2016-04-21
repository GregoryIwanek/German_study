#ifndef GUESSSENTENCESECTION
#define GUESSSENTENCESECTION
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLineEdit>
#include "wordcontainer.h"
#include "sentencearea.h"
#include "customscene.h"
class GuessSentenceSection:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    GuessSentenceSection();

    void setSceneFromMainWindow(CustomScene *myScene);

    void setMenu();
    void setButtons();

    void setBorderRect();
    void setWordContainers();
    void setColumn();
    void setRow(int y);
    void setSentenceAreas();
    void setInputComponents();
    void setSignNextWordContainerPositionToContainers();
    void setVariables();
    void checkWordContainerCollision(QPointF startPointOfChecked);

    QPointF getClosestGridPoint(QPointF point);

public slots:
    void sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer);
    void setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved);
    void setSession();
    void back();
    void clearSentence();
    void setGuessSentenceSectionVisible();
signals:
    void startButtonClicked();
    void backButtonClicked();
private:
    bool isWordContainerMoved = false;
    int endOfWordContainer = 0;
    CustomScene *scene;
    QList<SentenceArea*> sentenceAreaList;
    QList<WordContainer*> wordContainerList;
    QLineEdit *lineEdit;
    QPointF nextWordContainerPosition,*nextWordContainerPositionPointer;
    QString correctSequenceOfWords;
    QTime *systemTime;
};

#endif // GUESSSENTENCESECTION
