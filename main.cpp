#include "mainwindow.h"
#include <QApplication>
#include "apperiance.h"

Apperiance *apperiance;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    apperiance = new Apperiance();
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
