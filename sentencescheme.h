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

    //types of sentences
    void setTypeOfSentence();
    void setDeclarativeSentence();
    void setNegativeSentence();
    void setInterrogativeSentence();
    void setComplexSentence();

    //subject
    void setSubjectTypeSQLTable();
    void setSubjectType();
    void setSubjectData();

    //verb
    void setVerbTypeSQLTable();
    void setVerbType();
    void setVerbData();

    //adjective

    //no

    //noun
    void setNounTypeSQLTable();
    void setNounType();
    void setIfNounSingular();
    void setIfNounDefined();
    void setSQLColumn();
    void setNounData();

    QList<QString> getRolesOfWordsInSentence();

    void setQuerySQL(QString column);
    QString getQuerySQL();
    QList<QString> getQuerySQLList();
    void setIndex(int max);
    QList<int> getIndexList();

private:
    QList<QString> rolesOfWordsInSentence;
    QList<QString> querySQLList;
    QList<int> indexList;
    int numberOfSubsentenceses;
    int count=0;
    QString typeOfSentence;

    bool isSubjectDirect;
    QString subjectType, subjectTable;
    int subjectIndexDirect,
    subjectIndexIfNonDirect,
    singularPlurarIfNonDirect;

    QString verbType;
    int verbRowIndex;

    QString adjective;

    QString no;

    QString nounType;
    bool isNounSingular, isNounDefined;

    QString querySQL;
};

#endif // SENTENCESCHEME

