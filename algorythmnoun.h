#ifndef ALGORYTHMNOUN_H
#define ALGORYTHMNOUN_H
#include <QObject>
#include <QList>
#include <QtSql/QSql>
#include <QSqlQuery>
class AlgorythmNoun{
public:
    AlgorythmNoun();

    void setInputFromSentenceScheme(int nounMaxIndex = 20);

    void setData();
    void defineVariables();
    void setIfIsSubject(bool isNounASubject = false);
    void setGrammarCase();
    void setIfIsSingular();
    void setIfIsDefined();
    void defineNounArticle();
    void setArticleSQLTable();
    void setArticleIfSingular();
    void setArticleIfDefined();
    void setArticleAndNounGender(QString gender);
    void setArticleSQLIndex();
    void setArticleQuery();
    void defineNoun();
    void setNounSQLTable();
    void setNounColumn();
    void setQueryForPickingIndex();
    void setCorrespondingIndexResultsFromDataBase();
    void setNounSQLIndex();
    void setNounQuery();
    void defineTranslations();
    void setArticleTranslationQuery();
    void setNounTranslationQuery();

    QString getQueries();
    int getQueriesRowsIndex();

private:
    QString querySQLArticle, querySQLArticleTranslation, querySQLNoun, querySQLNounTranslation;
    QString articleTable, nounTable;
    QString nounCase, nounGender, nounArticleColumn, nounColumn;
    bool isSentenceSubject, isSingular, isDefined;
    int articleIndex, nounIndex;
    QList<int> indexListOfNouns;
    QSqlQuery query;

};

#endif // ALGORYTHMNOUN_H
