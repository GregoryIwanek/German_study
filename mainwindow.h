#ifndef MAINWINDOW
#define MAINWINDOW
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include "wordcontainer.h"
#include "sentencearea.h"
class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

    void setMainWindow();
    void setBorderRect();
    void setWordContainers();
    void setSentenceAreas();
    void setColumn();
    void setRow(int y);
    void setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved);
    void setVariables();

public slots:
    void sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer);
signals:

private:
    bool isWordContainerMoved = false;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QList<SentenceArea*> sentenceAreaList;
    QPointF nextWordContainerPosition;
};

#endif // MAINWINDOW

