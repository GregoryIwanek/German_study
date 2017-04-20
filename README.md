# German_study
*Qt C++ deskop program*

## What is German_study
German_study is a QT deskop program for learning German language.

## What was used to build 
To code and build this program were used:

**Tools**
* C++
* SQLite
* <a href="https://github.com/qtproject" title="qtproject">Qt framework</a>

**Pattern**
* elements of MVC

**Tested on**
* laptop

## How does it look like
Program is divided into two seperated sections and main menu.

**Main menu**

<img src="https://rawgit.com/GregoryIwanek/German_study/master/pictures/menu.png" title="menu" height="250" />

**GuessSentenceSection**

(SENTENCE button in main menu) is a game where user has to put WordContainers on SentenceArea in correct order. When it happens, translation into English language is provided.
User can use Hint, which will show picture with some grammar rules. Goal can be achieved by sending correct WordContainers to SentenceArea in correct order, or, typing down into LineEdit correct german sentence.

<img src="https://rawgit.com/GregoryIwanek/German_study/master/pictures/grammar_game.png" title="guess sentence" height="250" />

**FlashCardSection**

(FLASH CARD button in main menu) is a game where user has to pair corresponding words in WordContainers on screen. For each pair of words there is a translated and original word.

<img src="https://rawgit.com/GregoryIwanek/German_study/master/pictures/guess_game.png" title="flashcard game" height="250" />

## DONE:
**CLASSES**
* class MainWindow ( is main window of program)
* class MyApplication (contains MainWindow and will give access to data in futore)
* class MyApplicationData (contains general data, in future will contian settings)
* class Words ( picks word from SQL by generated query)
* class SentenceData (operates on given queries and create instances of Word class, also holds data about words from SQL)
* class SentenceScheme (generates sentences to guess and list of words)
* classes AlgorythmNoun/Verb etc. ( generates queries for picking words from SQL)
* class apperiance (instance is extern- for use in UI apperiance)
* class FlashCardSection which contains logic and UI of section ( it is a bridge between logic and UI)
* class GuessSentenceSection which contains logic and UI of section ( same as above)
* class MyButton (customized button with signals/slots)
* class WordContainer (contains information from Sentence class and displays texts from Word instances)

## TODO:
* algorythm for moving WordContainers in GSSection to second Sentence Area if there is no space left in a first one
* algorythm for removing gaps from both Sentence Areas at same time
* timer in FCSection
* settings to choose ( like category of words in FCSecion, number of words in FCSection etc.)


