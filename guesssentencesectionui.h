#ifndef GUESSSENTENCESECTIONUI_H
#define GUESSSENTENCESECTIONUI_H
#include <QObject>
#include <QList>
#include <QLineEdit>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include "mybutton.h"
#include "customscene.h"
#include "sentencearea.h"
#include <qmap.h>
class GuessSentenceSectionUI:public QObject {
    Q_OBJECT
public:
    GuessSentenceSectionUI();

    void setSceneFromParent(CustomScene *myScene);
    void setMenu();

    void buildUI();

    void setBorderRect();
    void setCollisionRects();
    void setSentenceAreaCollisionRect();
    void drawCollisionRect(QVector<QPointF> listOfPoints);
    void setSentenceAreas();
    void setUIComponents();
    void setButtons();
    void setUiTexts();
    void setInputUIComponents();

    void setMyButtonsMap();

    QPointF getClosestGridPoint(QPointF point);
    QList<SentenceArea *> getSentenceAreaList();
    MyButton *getMyButton(QString nameOfButton);
    QLineEdit *getMyLineEdit();

public slots:
    void back();
    void clearSentence();
    void checkIfSentenceCorrectButton();
    void setNewSentence();
    void updatePointsText(int number);
    void updateSentenceText(QString text);
    void updateResultText(bool isResultCorrect);
    void clearUIText(bool isCompleteClear);
    void sendLineEditData();
signals:
    void signalBack();
    void signalClearSentence();
    void signalCheckIfSentenceIsCorrectButton();
    void signalSetNewSentence();
    void signalSendLineEditData(QString text);
private:
    CustomScene *scene;
    MyButton *buttonBack, *buttonClear, *buttonCheck, *buttonStart;
    QGraphicsTextItem *points, *translation, *result;
    QLineEdit *lineEdit;
    QList<SentenceArea*> sentenceAreaList;

    QMap<QString, MyButton*> myButtonsMap;
};

#endif // GUESSSENTENCESECTIONUI_H
