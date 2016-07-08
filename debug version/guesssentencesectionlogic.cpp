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
    //sets main window scene as a scene to draw on
    scene = myScene;
}

void GuessSentenceSectionLogic::setSentenceAreaList(QList<SentenceArea *> mySentenceAreaList)
{
    //assign Sentence Areas from FCSection UI to lists
    sentenceAreaList = mySentenceAreaList;
}

void GuessSentenceSectionLogic::setWordContainerPositionOnSentenceArea()
{
    //sets starting position of first word container send to sentence area
    wordContainerPositionOnSentenceArea = QPointF(sentenceAreaList.first()->getWordContainerStartPosition().x() +20,
                                                  sentenceAreaList.first()->getWordContainerStartPosition().y());

    //sets pointer to that variable, for use in some methods
    wordContainerPositionOnSentenceAreaPointer = &wordContainerPositionOnSentenceArea;
}

void GuessSentenceSectionLogic::setWordContainerNextPositionToContainers()
{
    //sets position of next word container send to sentence area ( for use in MOVE slot of WordContainer)
    for (auto wordContainerToUpdate : wordContainersList)
    {
        wordContainerToUpdate->setNextContainerPositionInSentenceArea(wordContainerPositionOnSentenceAreaPointer);
    }
}

void GuessSentenceSectionLogic::updateWordContainerNextPositionOnSentenceArea(WordContainer *wordContainer, bool isOnSentenceArea)
{
    //updates position of next word container which will be send to sentence area after we send WC to sentence area
    if (isOnSentenceArea == true){
        wordContainerPositionOnSentenceArea.setX(wordContainerPositionOnSentenceArea.x() + wordContainer->boundingRect().width()+19);
        wordContainerPositionOnSentenceArea.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
        wordContainerPositionOnSentenceAreaPointer = &wordContainerPositionOnSentenceArea;
    }
    //updates position of next word container which will be send to sentence area after we send back one WC
    else {
        wordContainerPositionOnSentenceArea.setX(wordContainerPositionOnSentenceArea.x() - wordContainer->getWidthOfRect()-19);
        wordContainerPositionOnSentenceArea.setY(sentenceAreaList.first()->getWordContainerStartPosition().y());
        wordContainerPositionOnSentenceAreaPointer = &wordContainerPositionOnSentenceArea;
    }
}

void GuessSentenceSectionLogic::sendWordContainerToSentenceAreaAndBack(WordContainer *wordContainer)
{

    if (wordContainer->getIsOnSentenceArea()==false)
    {
        //update correct indexs on list of Word Containers on sentence area after we send them to
        setIndexOfWordContainerOnSentenceArea(wordContainer);
        wordContainer->setIsOnSentenceArea(true);
        updateSentence(wordContainer);
    }
    else
    {
        //update correct indexs on list of Word Containers on sentence area after we send them back
        setIndexOfWordContainerOnSentenceArea(wordContainer);
        wordContainer->setIsOnSentenceArea(false);
        updateSentence(wordContainer);
    }
}

void GuessSentenceSectionLogic::removeGapFromSentenceArea(WordContainer *wordContainer)
{
    //remove extra gap (20px) between WC send to sentence area ( sometimes happened beacouse of round() method)
    for (auto wordContainerUpdate : wordContainersList)
    {
        if (wordContainerUpdate->getIndexOnSentenceArea() > -1 && wordContainerUpdate->getIndexOnSentenceArea() > wordContainer->getIndexOnSentenceArea())
        {
            wordContainerUpdate->setPos(QPointF(wordContainerUpdate->pos().x()-(wordContainer->getWidthOfRect()+20), wordContainerUpdate->pos().y()));
        }
    }
}

void GuessSentenceSectionLogic::updateColorOfCorrectWordContainers(bool isAnswerCorrect)
{
    //sets color of WC after we click CHECK
    for (auto wordContainerColor : wordContainersList)
    {
        if (isAnswerCorrect == true)
        {
            //sets red/green to word containers
            updateColorOfWordContainersIfAnswerCorrect(wordContainerColor);
        }
        else
        {
            //sets red to all word containers when answer incorrect
            wordContainerColor->setBrush(apperiance->brushRed);
        }
    }
}

void GuessSentenceSectionLogic::updateColorOfWordContainersIfAnswerCorrect(WordContainer *wordContainerToColor)
{
    //update color of WC after we click CHECK button and answer is correct
    if (wordContainerToColor->getIsOnSentenceArea() == true)
    {
        //sets green for correct one
        wordContainerToColor->setBrush(apperiance->brushGreen);
    }
    else
    {
        //sets color red for rest of the Word Containers
        wordContainerToColor->setBrush(apperiance->brushRed);
    }
}

void GuessSentenceSectionLogic::keyPressEvent(QKeyEvent *event)
{
    //possible keyboard keys to play with
    if (event->key() == Qt::Key_Space && sentence == NULL)
    {
        //sets new sentence to solve
        setNewSentence();
    }
    else if (event->key() == Qt::Key_Space && sentenceInputByUserList.isEmpty() == false && sentence->getIfSentenceChecked() == false)
    {
        //checks result
        checkIfSentenceIsCorrect();
    }
    else if (event->key() == Qt::Key_Space && sentence->getIfSentenceChecked() == true)
    {
        //clears scene from sentence
        clearSentence();
    }
}

void GuessSentenceSectionLogic::setWordContainers(Sentence *sentence)
{
    //sets row of word containers after we click START
    setRow(sentence);
}

void GuessSentenceSectionLogic::setRow(Sentence *sentence)
{
    //sets column of word containers after START clicked
    for (int y=0, n=1; y<n; ++y)
    {
        setColumn(y, sentence);
    }
}

void GuessSentenceSectionLogic::setColumn(int y, Sentence *sentence)
{
    //sets word containers in row and columns and sets connections
    for (int x=0, n=sentence->sentenceDataPointer->getListOfWordsInRandomOrder().size(); x<n; ++x)
    {
        defineWordContainers(x,y,sentence);
        setWordContainerConnections(wordContainersList.last());
    }
}

void GuessSentenceSectionLogic::defineWordContainers(int x, int y, Sentence *sentence)
{
    //steps to define word containers on a scene, defines position, information, adds to list and scene and if it's out of window
    WordContainer *wordContainer = new WordContainer(sentence->sentenceDataPointer->getListOfWordsInRandomOrder()[x]);
    wordContainer->setSectionItBelongsTo("GSSection");
    putWordContainerOnBoard(wordContainer, y);
    endOfWordContainer += wordContainer->boundingRect().width() +20;
    wordContainersList.append(wordContainer);
    this->scene->addItem(wordContainer);
    checkIfWordContainerInCollision(wordContainer, y, true, false);
}

void GuessSentenceSectionLogic::putWordContainerOnBoard(WordContainer *wordContainer, int y)
{
    //sets starting position of created word containers after we click START
    wordContainer->setPos(QPointF(80+endOfWordContainer, 240 + (y+rowIndex)*(wordContainer->boundingRect().height()+20)));
    wordContainer->setStartPosition(wordContainer->pos());
}

void GuessSentenceSectionLogic::setWordContainerConnections(WordContainer *wordContainer)
{
    //sets connections beetwen word containers and Logic
    connect(wordContainer,SIGNAL(stopped(WordContainer*,bool)),this,SLOT(updateWordContainerNextPositionOnSentenceArea(WordContainer*,bool)));
    connect(wordContainer,SIGNAL(clicked(WordContainer*)),this,SLOT(sendWordContainerToSentenceAreaAndBack(WordContainer*)));
}

bool GuessSentenceSectionLogic::checkIfWordContainerInCollision(WordContainer *wordContainer, int y, bool checkBoard, bool checkSentenceArea)
{
    //checks if word container collide with invisible Collision Lines of Sentence Area ( if it's out of sentence area)
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
    //make word containers in second row upon building, when they are out of window
    ++rowIndex;
    endOfWordContainer = 0;
    putWordContainerOnBoard(wordContainer, y);
    endOfWordContainer += wordContainer->boundingRect().width() +20;
}

void GuessSentenceSectionLogic::setIndexOfWordContainerOnSentenceArea(WordContainer *wordContainer)
{
    //update index list of Word Containers on Sentence Area after we send back
    if (wordContainer->getIsOnSentenceArea() == true){
        --indexOfWordContainerOnSentenceArea;
        removeGapFromSentenceArea(wordContainer);
        updateIndexOfWordContainersOnSentenceArea(wordContainer->getIndexOnSentenceArea());
    }
    else
    {
        //update index list of WC on sentence area after we send to
        wordContainer->setIndexOnSentenceArea(indexOfWordContainerOnSentenceArea);
        ++indexOfWordContainerOnSentenceArea;
    }
}

void GuessSentenceSectionLogic::updateIndexOfWordContainersOnSentenceArea(int index)
{
    //sets new index of word containers on sentence area ( if we sent back container from the middle of sentence area)
    for (auto wordContainerUpdate : wordContainersList)
    {
        if (wordContainerUpdate->getIsOnSentenceArea() == true && wordContainerUpdate->getIndexOnSentenceArea() > index){
            wordContainerUpdate->setIndexOnSentenceArea(wordContainerUpdate->getIndexOnSentenceArea()-1);
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
    //resets sentence, so we can create new one
    for (auto wordContainerRemoved : wordContainersList)
    {
        //remove word containers from scene
        scene->removeItem(wordContainerRemoved);
        delete wordContainerRemoved;
    }

    //resets variables
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
        wordContainer->setIndexOnSentenceArea(-1);
    }
}
