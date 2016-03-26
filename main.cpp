#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include "apperiance.h"

Apperiance *apperiance;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    apperiance = new Apperiance();
    MainWindow mainWindow;
    mainWindow.show();
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("C:/Users/Grzegorz Iwanek/Desktop/Qt/German_Study/German.db");
    return a.exec();
}
