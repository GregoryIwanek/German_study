#ifndef MYAPPLICATION
#define MYAPPLICATION

#include "mainwindow.h"
#include "myapplicationdata.h"

class MyApplication{

public:
    MyApplication();

    //public methods
    void setMainWindowVisible();

    //public attributes
    MyApplicationData myApplicationData;
    MainWindow mainWindow;

};

#endif // MYAPPLICATION
