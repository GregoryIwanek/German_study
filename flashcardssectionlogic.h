#ifndef FLASHCARDSSECTIONLOGIC_H
#define FLASHCARDSSECTIONLOGIC_H
#include <QObject>
#include <QList>
#include <QKeyEvent>
#include "word.h"
#include "sentence.h"
#include "customscene.h"
#include "wordcontainer.h"

class FlashCardSectionLogic:public QObject{
    Q_OBJECT
public:
    FlashCardSectionLogic();

    void setSceneFromParent(CustomScene *myScene);
    void setConnections(WordContainer *wcToConnect);

    void setContainersOnScene();
    void setWordsDefinition(Sentence *sentence);
    void setRandomListOrder(QList<Word *> list);
    void setRow(int rowNumber, Sentence *sentence);
    void setColumn(int rowIndex);
    void setFlashCards(int rowNumber, int columnNumber);
    void setVisibilityOfWordContainers(WordContainer *wcGerman, WordContainer *wcTranslation);
    void setUncheckWordContainers(WordContainer *wcGerman, WordContainer *wcTranslation);
    void setCompareClickedWordContainers();
    void setWordsGermanWordsTranslation();
    void setClearWordsGermanWordsTranslation();

public slots:
    void setNewSession();
    void setVisibilityAfterClick(WordContainer *wordContainerClicked);
    void resetSession();
signals:

private:
    CustomScene *scene;
    QList<Word*> listOfWords;
    QList<Word*> listOfWordsTranslation;
    QList<Word*> listOfWordsGerman;
    QList<Word*> listOfWordsRandomOrder;
    QList<WordContainer*> listOfContainersToCompare;
    QList<WordContainer*> listOfContainersOnScene;
    QString wordOneGerman, wordOneTranslation, wordTwoGerman, wordTwoTranslation;
    bool isSessionInProgress = false;
    int count = 0;
    int countWordIndex = 0;
    int indexToPick = 0;
    int numberOfPickedWordsToRandomList = 0;
};

#endif // FLASHCARDSSECTIONLOGIC_H
