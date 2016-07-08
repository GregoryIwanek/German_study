#ifndef GUESSSENTENCESECTIONLOGIC_H
#define GUESSSENTENCESECTIONLOGIC_H
#include <QObject>
#include "customscene.h"
#include "sentence.h"
#include <QList>
#include <QTime>
#include <QKeyEvent>
#include "wordcontainer.h"
#include "sentencearea.h"
class GuessSentenceSectionLogic:public QObject{
    Q_OBJECT
public:
    GuessSentenceSectionLogic();

    void setSceneFromParent(CustomScene *myScene);
    void setSentenceAreaList(QList<SentenceArea*> mySentenceAreaList);

    void setWordContainerPositionOnSentenceArea();
    void setWordContainerNextPositionToContainers();
    void setWordContainers(Sentence *sentence);
    void setRow(Sentence *sentence);
    void setColumn(int x, Sentence *sentence);
    void defineWordContainers(int x, int y, Sentence *sentence);
    void putWordContainerOnBoard(WordContainer *wordContainer, int y);
    void setWordContainerConnections(WordContainer *wordContainer);
    void setIndexOfWordContainerOnSentenceArea(WordContainer *wordContainer);
    void updateIndexOfWordContainersOnSentenceArea(int index);
    void updateSentenceTextToDisplay();

    bool checkIfWordContainerInCollision(WordContainer *wordContainer, int y, bool checkBoard, bool checkSentenceArea);
    void wordContainerOutOfBoard(WordContainer *wordContainer, int y);
    bool checkIfWordContainerOutOfSentenceArea(WordContainer *wordContainer);

public slots:
    void setNewSentence();
    void checkIfSentenceIsCorrect();
    void checkIfSentenceIsCorrectInLineEdit(QString text);
    void clearSentence();
    void updatePoints(bool increased);
    void updateSentence(WordContainer *wordContainer);
    void updateWordContainerNextPositionOnSentenceArea(WordContainer *wordContainer, bool isOnSentenceArea);
    void sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer);
    void removeGapFromSentenceArea(WordContainer *wordContainer);
    void updateColorOfCorrectWordContainers(bool isAnswerCorrect);
    void updateColorOfWordContainersIfAnswerCorrect(WordContainer *wordContainerToColor);
    void keyPressEvent(QKeyEvent *event);

signals:
    void sentenceCreated(QString sentenceText);
    void sentenceChanged();
    void pointsChanged(int points);
    void resultChanged(bool isResultCorrect);
    void clearUITexts(bool isCompleteClear);
    void keyStartPressed();

private:
    CustomScene *scene;
    QList<SentenceArea *> sentenceAreaList;
    QList<WordContainer *> wordContainersList;
    QList<QString> sentenceInputByUserList;
    Sentence *sentence = NULL;

    int endOfWordContainer = 0, rowIndex=0;
    int indexOfWordContainerOnSentenceArea =0;
    int pointsOfPlayer = 0;

    QString sentenceString, translationString;

    QPointF wordContainerPositionOnSentenceArea, *wordContainerPositionOnSentenceAreaPointer;

    QTime *systemTime;
};

#endif // GUESSSENTENCESECTIONLOGIC_H
