#ifndef GUESSSENTENCESECTION
#define GUESSSENTENCESECTION
#include <QObject>
#include <QGraphicsItem>
#include "guesssentencesectionui.h"
#include "guesssentencesectionlogic.h"
#include "customscene.h"

class GuessSentenceSection:public QObject{
    Q_OBJECT
public:
    GuessSentenceSection();
    friend class MainWindow;

    void setSceneFromMainWindow(CustomScene *myScene);
    void setGuessSentenceSectionUI();
    void setGuessSentenceSectionLogic();

    void setConnectionsForSection();
public slots:
    void keyPressEvent(QKeyEvent *event);
signals:
    void keyPressed(QKeyEvent *event);
private:
    CustomScene *scene;
    GuessSentenceSectionUI *guessSentenceSectionUI;
    GuessSentenceSectionLogic * guessSentenceSectionLogic;
};

#endif // GUESSSENTENCESECTION
