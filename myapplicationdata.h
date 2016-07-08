#ifndef MYAPPLICATIONDATA
#define MYAPPLICATIONDATA
#include <QTime>
#include <stdlib.h>
class MyApplicationData{

public:
    MyApplicationData();

    void setRandom();

private:
    QTime *systemTime;
};

#endif // MYAPPLICATIONDATA

