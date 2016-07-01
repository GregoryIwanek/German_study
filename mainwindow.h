#ifndef MAINWINDOW
#define MAINWINDOW
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLineEdit>
#include "mybutton.h"
#include "wordcontainer.h"
#include "sentencearea.h"
#include "customscene.h"
#include "guesssentencesection.h"
#include "flashcardssection.h"
class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

    void setMainWindow();
    void setMainMenu();
    void setGuessSentenceSectionMenu();
    void setConnections();
    void keyPressEvent(QKeyEvent *event);

    void setButtonsVisible();

public slots:
    void setGuessSentenceSectionVisible();
    void setFlashCardSectionVisible();
    void setMainWindowVisible(QObject *section);
signals:
    void startButtonClicked();
    void keyPressed(QKeyEvent*);
private:
    QGraphicsView *view;
    CustomScene *scene;
    MyButton *buttonStart, *buttonFlashCards, *buttonOptions, *buttonQuit;
};

#endif // MAINWINDOW

