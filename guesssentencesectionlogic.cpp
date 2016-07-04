#include "guesssentencesectionlogic.h"
#include <QList>
#include <QGraphicsItem>
#include <stdlib.h>
#include <typeinfo.h>
GuessSentenceSectionLogic::GuessSentenceSectionLogic()
{

}

void GuessSentenceSectionLogic::setSceneFromParent(CustomScene *myScene)
{
    scene = myScene;
}

void GuessSentenceSectionLogic::setSentenceAreaList(QList<SentenceArea *> mySentenceAreaList)
{
    sentenceAreaList = mySentenceAreaList;
}

void GuessSentenceSectionLogic::setWordContainerPositionOnSentenceArea()
{
    wordContainerPositionOnSentenceArea = QPointF(sentenceAreaList.first()->getWordContainerStartPosition().x() +20,
                                                  sentenceAreaList.first()->getWordContainerStartPosition().y());
    wordContainerPositionOnSentenceAreaPointer = &wordContainerPositionOnSentenceArea;
}

void GuessSentenceSectionLogic::setWordContainerNextPositionToContainers()
{
    for (auto i=0, n=wordContainersList.size(); i<n; i++){
        wordContainersList[i]->setNextContainerPositionInSentenceArea(wordContainerPositionOnSentenceAreaPointer);
    }
}

void GuessSentenceSectionLogic::updateWordContainerNextPositionOnSentenceArea(WordContainer *wordContainer, bool isOnSentenceArea)
{
    if (isOnSentenceArea == true){
        wordContainerPositionOnSentenceArea.setX(wordContainerPositionOnSentenceArea.x() + wordContainer->boundingRect().width()+19);
        wordContainerPositionOnSentenceArea.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
        wordContainerPositionOnSentenceAreaPointer = &wordContainerPositionOnSentenceArea;
    }
    else {
        wordContainerPositionOnSentenceArea.setX(wordContainerPositionOnSentenceArea.x() - wordContainer->getWidthOfRect()-19);
        wordContainerPositionOnSentenceArea.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
        wordContainerPositionOnSentenceAreaPointer = &wordContainerPositionOnSentenceArea;
    }
}

void GuessSentenceSectionLogic::sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer)
{
    if (wordContainer->getIsOnSentenceArea()==false) {
        setIndexOfWordContainerOnSentenceArea(wordContainer);
        wordContainer->setIsOnSentenceArea(true);
        updateSentence(wordContainer);
    }
    else {
        setIndexOfWordContainerOnSentenceArea(wordContainer);
        wordContainer->setIsOnSentenceArea(false);
        updateSentence(wordContainer);
    }
}

void GuessSentenceSectionLogic::removeGapFromSentenceArea(WordContainer *wordContainer)
{
    for (auto i=0, n=wordContainersList.size(); i<n; ++i){

        if (wordContainersList[i]->getIndexOnSentenceArea() > -1 &&
                wordContainersList[i]->getIndexOnSentenceArea() > wordContainer->getIndexOnSentenceArea()){

            wordContainersList[i]->setPos(QPointF(wordContainersList[i]->pos().x()-(wordContainer->getWidthOfRect()+20),
                                                  wordContainersList[i]->pos().y()));
        }
    }
}

void GuessSentenceSectionLogic::updateColorOfCorrectWordContainers(bool isAnswerCorrect)
{
    for (auto i=0, n=wordContainersList.size(); i<n; ++i){
        if (isAnswerCorrect == true){
            updateColorOfWordContainersIfAnswerCorrect(i);
        }
        else wordContainersList[i]->setBrush(apperiance->brushRed);
    }
}

void GuessSentenceSectionLogic::updateColorOfWordContainersIfAnswerCorrect(int index)
{
    if (wordContainersList[index]->getIsOnSentenceArea() == true){
        wordContainersList[index]->setBrush(apperiance->brushGreen);
    }
    else wordContainersList[index]->setBrush(apperiance->brushRed);
}

void GuessSentenceSectionLogic::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && sentence == NULL){
        setNewSentence();
    }
    else if (event->key() == Qt::Key_Space
             && sentenceInputByUserList.isEmpty() == false && sentence->getIfSentenceChecked() == false){
        checkIfSentenceIsCorrect();
    }
    else if (event->key() == Qt::Key_Space && sentence->getIfSentenceChecked() == true){
        clearSentence();
    }
}

void GuessSentenceSectionLogic::setWordContainers(Sentence *sentence)
{
    setRow(sentence);
}

void GuessSentenceSectionLogic::setRow(Sentence *sentence)
{
    for (int y=0, n=1; y<n; ++y){
        setColumn(y, sentence);
    }
}

void GuessSentenceSectionLogic::setColumn(int y, Sentence *sentence)
{
    for (int x=0, n=sentence->sentenceDataPointer->getListOfWordsInRandomOrder().size(); x<n; ++x)
    {
        defineWordContainers(x,y,sentence);
        setWordContainerConnections(wordContainersList.last());
    }
}

void GuessSentenceSectionLogic::defineWordContainers(int x, int y, Sentence *sentence)
{
    WordContainer *wordContainer = new WordContainer(sentence->sentenceDataPointer->getListOfWordsInRandomOrder()[x]);
    putWordContainerOnBoard(wordContainer, y);
    endOfWordContainer += wordContainer->boundingRect().width() +20;
    wordContainersList.append(wordContainer);
    this->scene->addItem(wordContainer);
    checkIfWordContainerInCollision(wordContainer, y, true, false);
}

void GuessSentenceSectionLogic::putWordContainerOnBoard(WordContainer *wordContainer, int y)
{
    wordContainer->setPos(QPointF(80+endOfWordContainer, 240 + (y+rowIndex)*(wordContainer->boundingRect().height()+20)));
    wordContainer->setStartPosition(wordContainer->pos());
}

void GuessSentenceSectionLogic::setWordContainerConnections(WordContainer *wordContainer)
{
    connect(wordContainer,SIGNAL(stopped(WordContainer*,bool)),this,SLOT(updateWordContainerNextPositionOnSentenceArea(WordContainer*,bool)));
    connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
    //connect(wordContainer,SIGNAL(removeGapInSpace(WordContainer*)),this,SLOT(removeGapFromSentenceArea(WordContainer*)));
    //connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(updateSentence(WordContainer*)));
}

bool GuessSentenceSectionLogic::checkIfWordContainerInCollision(WordContainer *wordContainer, int y, bool checkBoard, bool checkSentenceArea)
{
    QList<QGraphicsItem *> collidingItems = wordContainer->collidingItems();

    for (int i=0, n=collidingItems.size(); i<n; ++i)
    {
        if (typeid(*(collidingItems[i])) == typeid(QGraphicsLineItem) && checkBoard == true)
        {
            wordContainerOutOfBoard(wordContainer, y);
            return true;
        }
        else if (typeid(*(collidingItems[i])) == typeid(QGraphicsLineItem) && checkSentenceArea == true)
        {
            return true;
        }
    }
    return false;
}

void GuessSentenceSectionLogic::wordContainerOutOfBoard(WordContainer *wordContainer, int y)
{
    ++rowIndex;
    endOfWordContainer = 0;
    putWordContainerOnBoard(wordContainer, y);
    endOfWordContainer += wordContainer->boundingRect().width() +20;
}

void GuessSentenceSectionLogic::setIndexOfWordContainerOnSentenceArea(WordContainer *wordContainer)
{
    if (wordContainer->getIsOnSentenceArea() == true){
        --indexOfWordContainerOnSentenceArea;
        removeGapFromSentenceArea(wordContainer);
        updateIndexOfWordContainersOnSentenceArea(wordContainer->getIndexOnSentenceArea());
    }
    else {
        wordContainer->setIndexOnSentenceArea(indexOfWordContainerOnSentenceArea);
        ++indexOfWordContainerOnSentenceArea;
    }
}

void GuessSentenceSectionLogic::updateIndexOfWordContainersOnSentenceArea(int index)
{
    for (auto i=0, n=wordContainersList.size(); i<n; ++i){
        if (wordContainersList[i]->getIsOnSentenceArea() == true && wordContainersList[i]->getIndexOnSentenceArea() > index){
            wordContainersList[i]->setIndexOnSentenceArea(wordContainersList[i]->getIndexOnSentenceArea()-1);
        }
    }
}

void GuessSentenceSectionLogic::updateSentenceTextToDisplay()
{
    sentenceString.append(sentence->sentenceDataPointer->getCorrectSentenceString());
    translationString.append(sentence->sentenceDataPointer->getCorrectTranslationString());
}

void GuessSentenceSectionLogic::setNewSentence()
{
    if (sentence == NULL){
        sentence = new Sentence(QString("GSSection"), QString("none"));
        setWordContainerPositionOnSentenceArea();
        setWordContainers(sentence);
        setWordContainerNextPositionToContainers();
        updateSentenceTextToDisplay();
        emit sentenceCreated(translationString);
    }
}

void GuessSentenceSectionLogic::checkIfSentenceIsCorrect()
{
    if (sentenceInputByUserList.isEmpty() == false){
        if (sentence->sentenceDataPointer->getCorrectSentence() == sentenceInputByUserList && sentence->getIfSentenceChecked() == false){
            updatePoints(true);
            updateColorOfCorrectWordContainers(true);
            sentence->setSentenceChecked(true);
        }
        else if (sentence->getIfSentenceChecked() == false){
            updatePoints(false);
            updateColorOfCorrectWordContainers(false);
            sentence->setSentenceChecked(true);
        }
    }
}

void GuessSentenceSectionLogic::checkIfSentenceIsCorrectInLineEdit(QString text)
{
    if (sentence != NULL){
        if (sentence->getIfSentenceChecked() == false && sentence->sentenceDataPointer->getCorrectSentenceString() == text){
            updatePoints(true);
            sentence->setSentenceChecked(true);
        }
        else if (sentence->getIfSentenceChecked() == false){
            updatePoints(false);
            sentence->setSentenceChecked(true);
        }
    }
}

void GuessSentenceSectionLogic::clearSentence()
{
    for (auto i=0, n=wordContainersList.size(); i<n; ++i){
        scene->removeItem(wordContainersList[i]);
        delete wordContainersList[i];
    }
    wordContainersList.clear();
    sentence = NULL;
    sentenceString = " ";
    translationString = " ";
    sentenceInputByUserList.clear();
    endOfWordContainer = 0;
    rowIndex = 0;
    indexOfWordContainerOnSentenceArea = 0;
    emit clearUITexts(false);
}

void GuessSentenceSectionLogic::updatePoints(bool increased)
{
    if (increased == true){
        ++pointsOfPlayer;
        emit resultChanged(true);
    }
    else if(increased == false && pointsOfPlayer > 0){
        --pointsOfPlayer;
        emit resultChanged(false);
    }
    else emit resultChanged(false);

    emit pointsChanged(pointsOfPlayer);
}

void GuessSentenceSectionLogic::updateSentence(WordContainer *wordContainer)
{
    if (wordContainer->getIsOnSentenceArea() == true){
        sentenceInputByUserList.append(wordContainer->getTextFromWord());
    }
    else {
        sentenceInputByUserList.removeAt(wordContainer->getIndexOnSentenceArea());
        //updateIndexOfWordContainersOnSentenceArea(wordContainer->getIndexOnSentenceArea());
        wordContainer->setIndexOnSentenceArea(-1);
    }
}
