#ifndef ALGORYTHMNOUN_H
#define ALGORYTHMNOUN_H
#include <QObject>

class AlgorythmNoun{
public:
    AlgorythmNoun();

    void setData();
    void defineVariables();
    void setIfIsSubject(bool isNounASubject = false);
    void setNounSQLTable();
    void setGrammarCase();
    void setIfIsSingular();
    void setIfIsDefined();
    void defineNounArticle();
    void setArticleSQLTable();
    void setArticleIfSingular();
    void setArticleIfDefined();
    void setArticleSQLIndex();

private:
    QString querySQLArticle, querySQLNoun;
    QString articleTable, nounTable;
    QString nounCase, nounArticleColumn;
    bool isSentenceSubject, isSingular, isDefined;
    int articleIndex;
};

#endif // ALGORYTHMNOUN_H
