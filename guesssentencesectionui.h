#ifndef GUESSSENTENCESECTIONUI_H
#define GUESSSENTENCESECTIONUI_H
#include <QObject>
#include <QList>
#include <QLineEdit>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "mybutton.h"
#include "customscene.h"
#include "sentencearea.h"
#include <qmap.h>
#include <QGraphicsItem>

class GuessSentenceSectionUI:public QObject {
    Q_OBJECT
public:
    GuessSentenceSectionUI();
    friend class GuessSentenceSection;

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
    void setHintImage();

    void setMyButtonsMap();
    void addToList(QGraphicsItem *item);

    QPointF getClosestGridPoint(QPointF point);
    QList<SentenceArea *> getSentenceAreaList();
    MyButton *getMyButton(QString nameOfButton);
    QLineEdit *getMyLineEdit();
    QList<QGraphicsItem *> getGraphicsItemList();

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
    void showHideHint();
signals:
    void signalBack(QObject *section);
    void signalClearSentence();
    void signalCheckIfSentenceIsCorrectButton();
    void signalSetNewSentence();
    void signalSendLineEditData(QString text);
    void signalShowHint();
private:
    CustomScene *scene;
    MyButton *buttonBack, *buttonClear, *buttonCheck, *buttonStart, *buttonHint;
    QGraphicsTextItem *points, *translation, *result;
    QGraphicsPixmapItem *hintImage;
    QLineEdit *lineEdit;
    QList<SentenceArea*> sentenceAreaList;

    QList<QGraphicsItem*> listOfItems;

    QMap<QString, MyButton*> myButtonsMap;
};

#endif // GUESSSENTENCESECTIONUI_H
