#ifndef GUESSSENTENCESECTION
#define GUESSSENTENCESECTION
#include <QObject>
#include "guesssentencesectionui.h"
#include "guesssentencesectionlogic.h"
#include "customscene.h"

class GuessSentenceSection:public QObject{
    Q_OBJECT
public:
    GuessSentenceSection();

    void setSceneFromMainWindow(CustomScene *myScene);
    void setGuessSentenceSectionUI();
    void setGuessSentenceSectionLogic();

    void setConnectionsSwitch(bool isConnected);
    void setConnectionsForSection();
public slots:
    void keyPressEvent(QKeyEvent *event);
    void switchConnections();
signals:
    void keyPressed(QKeyEvent *event);
private:
    CustomScene *scene;
    GuessSentenceSectionUI *guessSentenceSectionUI;
    GuessSentenceSectionLogic * guessSentenceSectionLogic;

    bool connectionsSwitch = true;
};

#endif // GUESSSENTENCESECTION
