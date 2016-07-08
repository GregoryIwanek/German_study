#include "myapplicationdata.h"

MyApplicationData::MyApplicationData()
{
    //sets seed with random for use in programm
    setRandom();
}

void MyApplicationData::setRandom()
{
    //sets random depending on current system time
    systemTime = new QTime();
    qsrand(time_t(systemTime));
}
