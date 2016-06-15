#ifndef FLASHCARDSSECTIONUI_H
#define FLASHCARDSSECTIONUI_H
#include <QObject>
#include "customscene.h"
#include "mybutton.h"

class FlashCardSectionUI:public QObject{
    Q_OBJECT
public:
    FlashCardSectionUI();

    void setSceneFromParent(CustomScene *myScene);
    void buildUI();
    void setMenu();
    void setUIComponents();
    void setButtons();
    void setUiTexts();

    void setBorderRect();
    void setMyButtonsMap();

    QPointF getClosestGridPoint(QPointF point);
private:
    CustomScene *scene;
    MyButton *buttonBack, *buttonClear, *buttonStart;
};
#endif // FLASHCARDSSECTIONUI_H
