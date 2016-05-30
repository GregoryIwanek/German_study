#include "myapplicationdata.h"

MyApplicationData::MyApplicationData()
{
    setRandom();
}

void MyApplicationData::setRandom()
{
    systemTime = new QTime();
    qsrand(time_t(systemTime));
}
