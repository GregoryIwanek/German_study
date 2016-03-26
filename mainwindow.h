#ifndef MAINWINDOW
#define MAINWINDOW
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLineEdit>
#include "wordcontainer.h"
#include "sentencearea.h"
#include "customscene.h"
class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

    void setMainWindow();
    void setBorderRect();
    void setWordContainers();
    void setColumn();
    void setRow(int y);
    void setSentenceAreas();
    void setInputComponents();
    void setNextWordContainerPosition(WordContainer *wordContainer, bool isWordContainerMoved);
    void setVariables();
    void checkWordContainerCollision(QPointF startPointOfChecked);

    QPointF getClosestGridPoint(QPointF point);

public slots:
    void sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer);
signals:

private:
    bool isWordContainerMoved = false;
    QGraphicsView *view;
    CustomScene *scene;
    QList<SentenceArea*> sentenceAreaList;
    QList<WordContainer*> wordContainerList;
    QLineEdit *lineEdit;
    QPointF nextWordContainerPosition;
    QString correctSequenceOfWords;
    QTime *systemTime;
};

#endif // MAINWINDOW

