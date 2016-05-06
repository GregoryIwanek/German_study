#ifndef GUESSSENTENCESECTIONNN
#define GUESSSENTENCESECTIONNN
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
#include "mybutton.h"
#include "wordcontainer.h"
#include "sentence.h"
#include "sentencearea.h"
#include "customscene.h"
#include "guesssentencesectionlogic.h"

class MyClass:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    MyClass();

    void setSceneFromMainWindow(CustomScene *myScene); //
    void setKeyEventFromMainWindow(QKeyEvent *event);
    void setGuessSentenceSectionLogic();

    void setMenu(); //
    void setButtons(); //
    void setUiTexts(); //
    void setUIComponents(); //
    void setInputUIComponents(); //
    void setBorderRect(); //
    void setConnections();

    void setWordContainers(Sentence *sentence);//
    void setColumn(Sentence *sentence);//
    void setRow(int y, Sentence *sentence);//
    void setSentenceAreas();//
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
    void setNewSentence();
    void checkIfSentenceCorrect();
    void updatePoints(bool increased);
    void checkIfSentenceInputInQLineEditIsCorrect();
    void updateColorOfCorrectWordContainers();
    void updateSentenceText();
    void updatePointsText();
    void updateResultText(bool isCorrect);
    void removeGapFromSentenceArea(WordContainer *wordContainer);
    void back();
    void clearSentence();
    void setGuessSentenceSectionVisible();
    void keyPressEvent(QKeyEvent *event);
signals:
    void pointsChanged();
    void sentenceChanged();
    void resultChanged(bool isCorrect);
    void keyStartPressed();
    void keyCheckPressed();
    void keyClearPressed();
private:
    GuessSentenceSectionLogic *guessSentenceSectionLogic;
    bool isWordContainerMoved = false;
    int pointsOfPlayer=0;
    int endOfWordContainer = 0;
    int indexOfWordContainerOnSentenceArea = 0;
    CustomScene *scene;
    QList<SentenceArea*> sentenceAreaList;
    QList<WordContainer*> wordContainerList;
    QList<Sentence*> sentenceList;
    QList<QString> sentenceInputByUserList;
    QGraphicsTextItem *points, *translation, *result;
    QString sentence;
    QLineEdit *lineEdit;
    QPointF nextWordContainerPosition,*nextWordContainerPositionPointer;
    QTime *systemTime;
    QKeyEvent *myKeyEvent;
};
#endif // GUESSSENTENCESECTIONNN
