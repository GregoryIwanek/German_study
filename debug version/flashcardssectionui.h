#ifndef FLASHCARDSSECTIONUI_H
#define FLASHCARDSSECTIONUI_H
#include <QObject>
#include <QGraphicsTextItem>
#include <QMap>
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
    MyButton *getMyButton(QString nameOfButton);

public slots:
    void back();

signals:
    void signalStart();
    void signalBack(QObject *section);
    void signalResetSession();

private:
    CustomScene *scene;
    MyButton *buttonBack, *buttonClear, *buttonStart;
    QGraphicsTextItem *time;
    QMap<QString, MyButton*> myButtonsMap;
};
#endif // FLASHCARDSSECTIONUI_H
