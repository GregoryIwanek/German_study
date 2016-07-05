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

    void setContainersOnScene();
    void setFlashCards(int rowNumber, int columnNumber, Sentence *sentence, int count);
    void setRow(int rowNumber, Sentence *sentence);
    void setColumn(int rowIndex, Sentence *sentence);
    void setRandomListOrder(QList<Word *> list);
    void setALoop(QList<Word *> list);
    void setConnections(Word *myWord);


public slots:
    void setNewSession();
    void setColorOfWordContainer(WordContainer *wordContainer);
signals:

private:
    CustomScene *scene;
    QList<Word*> listOfWords;
    QList<Word*> listOfWordsTranslation;
    QList<Word*> listOfWordsGerman;
    QList<Word*> listOfWordsRandomOrder;
    int count = 0;
    int countWordIndex = 0;
    int indexToPick;
    int numberOfPickedWordsToRandomList = 0;
};

#endif // FLASHCARDSSECTIONLOGIC_H
