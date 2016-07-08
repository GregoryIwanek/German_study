#ifndef ALGORYTHMNOUN_H
#define ALGORYTHMNOUN_H
#include <QObject>
#include <QList>
#include <QtSql/QSql>
#include <QSqlQuery>

class AlgorythmNoun{

public:
    AlgorythmNoun(bool isNounASubject);

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
    void setSubjectIndex();

    QString getQueryArticle();
    QString getQueryArticleTranslation();
    QString getQueryNoun();
    QString getQueryNounTranslation();
    QString getIfPlurarUndefined(QString toReturn);
    int getQueryArticleRowIndex();
    int getQueryNounRowIndex();
    int getSubjectIndex();

private:
    QString querySQLArticle, querySQLArticleTranslation, querySQLNoun, querySQLNounTranslation;
    bool isQueryArticleNounCombined = false;
    QString articleTable, nounTable;
    QString nounCase, nounGender, nounArticleColumn, nounColumn;
    bool isSentenceSubject = NULL, isSingular, isDefined;
    int articleIndex, nounIndex;
    int subjectIndex;
    QList<int> indexListOfNouns;
    QSqlQuery query;

};

#endif // ALGORYTHMNOUN_H
