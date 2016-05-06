#include "guesssentencesectionlogic.h"
#include <QList>
#include <QGraphicsItem>
#include <stdlib.h>
GuessSentenceSectionLogic::GuessSentenceSectionLogic()
{
    systemTime = new QTime();
    srand(time_t(systemTime));
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
    for (size_t i=0, n=wordContainersList.size(); i<n; i++){
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
    for (size_t i=0, n=wordContainersList.size(); i<n; ++i){

        if (wordContainersList[i]->getIndexOnSentenceArea() != NULL &&
                wordContainersList[i]->getIndexOnSentenceArea() > wordContainer->getIndexOnSentenceArea()){

            wordContainersList[i]->setPos(QPointF(wordContainersList[i]->pos().x()-(wordContainer->getWidthOfRect()+20),
                                                  wordContainersList[i]->pos().y()));
        }
    }
}

void GuessSentenceSectionLogic::updateColorOfCorrectWordContainers()
{
    for (size_t i=0, n=wordContainersList.size(); i<n; ++i){

        if (wordContainersList[i]->getIsOnSentenceArea() == true){
            wordContainersList[i]->setBrush(apperiance->brushGreen);
        }
        else wordContainersList[i]->setBrush(apperiance->brushRed);
    }
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
    for (int x=0, n=sentence->sentenceData.getListOfWordsInRandomOrder().size(); x<n; ++x)
    {
        defineWordContainers(x,y,sentence);
        setWordContainerConnections(wordContainersList.last());
    }
}

void GuessSentenceSectionLogic::defineWordContainers(int x, int y, Sentence *sentence)
{
    WordContainer *wordContainer = new WordContainer(sentence->sentenceData.getListOfWordsInRandomOrder()[x]);
    putWordContainerOnBoard(wordContainer, y);
    endOfWordContainer += wordContainer->boundingRect().width() +20;
    wordContainersList.append(wordContainer);
    this->scene->addItem(wordContainer);
    checkIfWordContainerOutOfBoard(wordContainer, y);
}

void GuessSentenceSectionLogic::putWordContainerOnBoard(WordContainer *wordContainer, int y)
{
    wordContainer->setPos(QPointF(60+endOfWordContainer, 220 + (y+rowIndex)*(wordContainer->boundingRect().height()+20)));
    wordContainer->setStartPosition(wordContainer->pos());
}

void GuessSentenceSectionLogic::setWordContainerConnections(WordContainer *wordContainer)
{
    connect(wordContainer,SIGNAL(stopped(WordContainer*,bool)),this,SLOT(updateWordContainerNextPositionOnSentenceArea(WordContainer*,bool)));
    connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
    //connect(wordContainer,SIGNAL(removeGapInSpace(WordContainer*)),this,SLOT(removeGapFromSentenceArea(WordContainer*)));
    //connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(updateSentence(WordContainer*)));
}

bool GuessSentenceSectionLogic::checkIfWordContainerOutOfBoard(WordContainer *wordContainer, int y)
{
    QList<QGraphicsItem *> collidingItems = wordContainer->collidingItems();
    for (int i=0, n=collidingItems.size(); i<n; ++i){
        if (typeid(*(collidingItems[i])) == typeid(QGraphicsLineItem)){
            ++rowIndex;
            endOfWordContainer = 0;
            putWordContainerOnBoard(wordContainer, y);
            endOfWordContainer += wordContainer->boundingRect().width() +20;
            return true;
        }
    }
    return false;
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
    for (size_t i=0, n=wordContainersList.size(); i<n; ++i){
        if (wordContainersList[i]->getIsOnSentenceArea() == true && wordContainersList[i]->getIndexOnSentenceArea() > index){
            wordContainersList[i]->setIndexOnSentenceArea(wordContainersList[i]->getIndexOnSentenceArea()-1);
        }
    }
}

void GuessSentenceSectionLogic::updateSentenceTextToDisplay()
{
    sentenceString.append(sentence->sentenceData.getCorrectSentenceString());
    translationString.append(sentence->sentenceData.getCorrectTranslationString());
}

void GuessSentenceSectionLogic::setNewSentence()
{
    if (sentence == NULL){
        sentence = new Sentence();
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
        if (sentence->sentenceData.getCorrectSentence() == sentenceInputByUserList && sentence->getIfSentenceChecked() == false){
            updatePoints(true);
            updateColorOfCorrectWordContainers();
            sentence->setSentenceChecked(true);
        }
        else if (sentence->getIfSentenceChecked() == false){
            updatePoints(false);
            updateColorOfCorrectWordContainers();
            sentence->setSentenceChecked(true);
        }
    }
}

void GuessSentenceSectionLogic::checkIfSentenceIsCorrectInLineEdit(QString text)
{
    if (sentence != NULL){
        if (sentence->getIfSentenceChecked() == false && sentence->sentenceData.getCorrectSentenceString() == text){
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
    for (size_t i=0, n=wordContainersList.size(); i<n; ++i){
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
        wordContainer->setIndexOnSentenceArea(NULL);
    }
}
