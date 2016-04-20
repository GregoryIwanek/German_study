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
    QBrush brushDarkRed;
    QBrush brushGreen;
    QBrush brushDarkGreen;
    QBrush brushBlue;
    QBrush brushDarkBlue;
    QBrush brushCyan;
    QBrush brushDarkCyan;
    QBrush brushMagnete;
    QBrush brushDarkMagneta;
    QBrush brushYellow;
    QBrush brushDarkYellow;
    QBrush brushGray;
    QBrush brushDarkGray;
    QBrush brushLightGray;
    QBrush brushTransparent;

    QBrush brushNULL;

    //textures
    QBrush brushMainMenuTexture;

    QPen blackPen;

    QFont fontComicSans;
private:

};

#endif // APPERIANCE

