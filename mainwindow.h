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
#include "guesssentencesection.h"
#include "flashcardssection.h"
class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

    void setMainWindow();
    void setMainMenu();
    void setGuessSentenceSectionMenu();
    void keyPressEvent(QKeyEvent *event);

public slots:
    void setGuessSentenceSectionVisible();
    void setFlashCardSectionVisible();
signals:
    void startButtonClicked();
    void keyPressed(QKeyEvent*);
private:
    QGraphicsView *view;
    CustomScene *scene;
    GuessSentenceSection *guessSentenceSection;
    FLashCardSection *flashCardSection;
};

#endif // MAINWINDOW

