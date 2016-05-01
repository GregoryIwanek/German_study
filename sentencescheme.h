#ifndef SENTENCESCHEME
#define SENTENCESCHEME
#include <QString>
#include <QList>

class SentenceScheme {

public:
    SentenceScheme();
    //void setHowManySubsentenceses();
    void updateScheme(QString update);
    void setExtraWords();
    void setDefineExtraWords();
    void setVariables();
    int getNumberOfExtraWords();

    //types of sentences
    void setTypeOfSentence(bool complexSentenceAllowed);
    void setDeclarativeSentence();
    void setNegativeSentence();
    void setInterrogativeSentence();
    void setComplexSentence();

    //subject
    void setSubjectTypeSQLTable();
    void setCase();
    void setSubjectType();
    void setSubjectData();
    void setSubjectTranslation();

    //verb
    void setVerbTypeSQLTable();
    void setVerbType();
    void setVerbData();
    void setVerbTranslation();

    //adjective

    //no

    //noun
    void setNounTypeSQLTable();
    void setNounType();
    void setIfNounSingular();
    void setIfNounDefined();
    void setSQLColumn();
    void setNounData();
    void setNounTranslation();

    //separator ( but, or, and etc.)
    void setSeparator();
    void setSeparatorTypeSQLTable();
    void setSeparatorType();
    void setSeparatorTranslation();

    QList<QString> getRolesOfWordsInSentence();

    void setQuerySQL(QString columnWord, QString columnTranslation);
    QString getQuerySQL();
    QList<QString> getQuerySQLList(bool returnQuerySQLList);
    void setIndex(int max);
    QList<int> getIndexList(bool returnIndexList);
    void increaseCount();

private:
    QList<QString> rolesOfWordsInSentence;
    QList<QString> querySQLList;
    QList<QString> querySQLTranslationList;
    QList<int> indexTranslationList;
    QList<int> indexList;
    int numberOfSubsentenceses;
    int numberOfExtraWords;
    int count;
    QString typeOfSentence;

    bool isSubjectDirect;
    QString subjectType, subjectTable;
    int subjectIndexDirect, subjectIndexIfNonDirect, singularPlurarIfNonDirect;

    QString verbType;
    int verbRowIndex;

    QString adjective;

    QString no;

    QString nounType;
    int nounTypeSwitch;
    bool isNounSingular, isNounDefined;

    QString separatorType;

    QString querySQL, querySQLTranslation;
};

#endif // SENTENCESCHEME

