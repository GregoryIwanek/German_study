#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include "apperiance.h"
#include "myapplication.h"

Apperiance *apperiance;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("C:/Users/Grzegorz Iwanek/Desktop/Qt/German_Study/German.db");
    myDB.open();
    apperiance = new Apperiance();
    MyApplication myApplication;
    return a.exec();
}
