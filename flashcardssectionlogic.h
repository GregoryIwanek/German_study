#ifndef FLASHCARDSSECTIONLOGIC_H
#define FLASHCARDSSECTIONLOGIC_H
#include <QObject>
#include "sentence.h"
#include "customscene.h"

class FlashCardSectionLogic:public QObject{
    Q_OBJECT
public:
    FlashCardSectionLogic();

    void setSceneFromParent(CustomScene *myScene);

    void setFlashCards(int rowNumber, int columnNumber, Sentence *sentence);
    void setRow(int rowNumber);
    void setColumn(int rowIndex);

public slots:
    void setNewSession();
signals:

private:
    CustomScene *scene;
    Sentence *sentence;
};

#endif // FLASHCARDSSECTIONLOGIC_H
