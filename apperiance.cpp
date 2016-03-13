#include "apperiance.h"
#include "wordcontainer.h"

Apperiance::Apperiance(){

    defineBrush();
    definePen();
    defineFont();
}

void Apperiance::defineBrush(){
    brushWhite.setColor(Qt::white);
    brushWhite.setStyle(Qt::SolidPattern);

    brushRed.setColor(Qt::red);
    brushRed.setStyle(Qt::SolidPattern);

    brushGreen.setColor(Qt::green);
    brushGreen.setStyle(Qt::SolidPattern);

    brushBlack.setColor(Qt::black);
    brushBlack.setStyle(Qt::SolidPattern);
}

void Apperiance::definePen(){
    blackPen.setColor(Qt::black);
    blackPen.setStyle(Qt::SolidLine);
}

void Apperiance::defineFont(){
    fontComicSans.setFamily("comic sans");
    fontComicSans.setPointSizeF(20);
}

QBrush Apperiance::getBrush(QBrush brushToGet){

    return brushToGet;
}




