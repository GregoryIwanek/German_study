#ifndef ALGORYTHMEXPRESSION_H
#define ALGORYTHMEXPRESSION_H
#include <QObject>

class AlgorythmExpression:public QObject{
    Q_OBJECT
public:
    AlgorythmExpression();

    void setData();
    void defineExpression();
    void setExpressionSQLTable();
    void setExpressionSQLColumn();
    void setExpressionSQLRow();
    void setExpressionQuery();
    void defineTranslation();
    void setExpressionTranslationSQLColumn();
    void setExpressionTranslationQuery();

    QString getQuery();
    QString getQueryTranslation();
    int getExpressionIndex();

signals:

private:
    QString expressionTable;
    QString expressionColumn, expressionTranslationColumn;
    QString querySQLExpression, querySQLExpressionTranslation;
    int expressionIndex;
};

#endif // ALGORYTHMEXPRESSION_H
