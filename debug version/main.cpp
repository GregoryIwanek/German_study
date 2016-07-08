#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include "apperiance.h"
#include "myapplication.h"

Apperiance *apperiance;

int main(int argc, char *argv[])
{
    //main application
    QApplication a(argc, argv);

    //connection to database
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("German.db");
    myDB.open();

    //setting new instance of apperiance (holds items like brush, pen, texture etc.)
    apperiance = new Apperiance();

    //sets instance of MyApplication
    MyApplication myApplication;

    return a.exec();
}
