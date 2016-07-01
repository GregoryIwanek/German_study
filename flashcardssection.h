#ifndef FLASHCARDSSECTION_H
#define FLASHCARDSSECTION_H
#include <QObject>
#include "customscene.h"
#include "flashcardssectionlogic.h"
#include "flashcardssectionui.h"

class FlashCardSection:public QObject{
    Q_OBJECT
public:
    FlashCardSection();
    friend class MainWindow;

    void setSceneFromMainWindow(CustomScene *myScene);
    void setFlashCardSectionUI();
    void setFlashCardSectionLogic();

    void setConnectionsSwitch(bool isConnected);
    void setConnectionsForSection();
public slots:
    void keyPressEvent(QKeyEvent *event);
    void switchConnections();
signals:
    void keyPressed(QKeyEvent *event);
private:
    CustomScene *scene;
    FlashCardSectionUI *flashCardSectionUI;
    FlashCardSectionLogic *flashCardSectionLogic;
};

#endif // FLASHCARDSSECTION_H
