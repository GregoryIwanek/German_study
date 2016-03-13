#ifndef APPERIANCE
#define APPERIANCE
#include <QBrush>
#include <QPen>
#include <QFont>

class Apperiance{

public:
    Apperiance();

    void defineBrush();
    void definePen();
    void defineFont();
    QBrush getBrush(QBrush brushToGet);

    //public attributes
    QBrush brushWhite;
    QBrush brushBlack;
    QBrush brushRed;
    QBrush brushGreen;

    QPen blackPen;

    QFont fontComicSans;
private:

};

#endif // APPERIANCE

