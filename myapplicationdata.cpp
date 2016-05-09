#include "myapplicationdata.h"

MyApplicationData::MyApplicationData()
{
    setRandom();
}

void MyApplicationData::setRandom()
{
    systemTime = new QTime();
    srand(time_t(systemTime));
}
