#ifndef FLASHCARDSSECTIONLOGIC_H
#define FLASHCARDSSECTIONLOGIC_H
#include <QObject>
#include "customscene.h"

class FlashCardSectionLogic:public QObject{
    Q_OBJECT
public:
    FlashCardSectionLogic();

    void setSceneFromParent(CustomScene *myScene);

private:
    CustomScene *scene;
};

#endif // FLASHCARDSSECTIONLOGIC_H
