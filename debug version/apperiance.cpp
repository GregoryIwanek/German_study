#include "apperiance.h"
#include "wordcontainer.h"

Apperiance::Apperiance()
{
    //steps to define apperiance components which can be used in this application
    defineBrush();
    definePen();
    defineFont();
    definePalette();
    definePixmap();
}

void Apperiance::defineBrush()
{
    //definition of different brushesh
    brushWhite.setStyle(Qt::SolidPattern);
    brushWhite.setColor(Qt::white);

    brushBlack.setStyle(Qt::SolidPattern);
    brushBlack.setColor(Qt::black);

    brushRed.setStyle(Qt::SolidPattern);
    brushRed.setColor(Qt::red);

    brushDarkRed.setStyle(Qt::SolidPattern);
    brushDarkRed.setColor(Qt::darkRed);

    brushGreen.setStyle(Qt::SolidPattern);
    brushGreen.setColor(Qt::green);

    brushDarkGreen.setStyle(Qt::SolidPattern);
    brushDarkGreen.setColor(Qt::darkGreen);

    brushBlue.setStyle(Qt::SolidPattern);
    brushBlue.setColor(Qt::blue);

    brushDarkBlue.setStyle(Qt::SolidPattern);
    brushDarkBlue.setColor(Qt::darkBlue);

    brushCyan.setStyle(Qt::SolidPattern);
    brushCyan.setColor(Qt::cyan);

    brushDarkCyan.setStyle(Qt::SolidPattern);
    brushDarkCyan.setColor(Qt::darkCyan);

    brushMagnete.setStyle(Qt::SolidPattern);
    brushMagnete.setColor(Qt::magenta);

    brushDarkMagneta.setStyle(Qt::SolidPattern);
    brushDarkMagneta.setColor(Qt::darkMagenta);

    brushYellow.setStyle(Qt::SolidPattern);
    brushYellow.setColor(Qt::yellow);

    brushDarkYellow.setStyle(Qt::SolidPattern);
    brushDarkYellow.setColor(Qt::darkYellow);

    brushGray.setStyle(Qt::SolidPattern);
    brushGray.setColor(Qt::gray);

    brushDarkGray.setStyle(Qt::SolidPattern);
    brushDarkGray.setColor(Qt::darkGray);

    brushLightGray.setStyle(Qt::SolidPattern);
    brushLightGray.setColor(Qt::lightGray);

    brushTransparent.setStyle(Qt::SolidPattern);
    brushTransparent.setColor(Qt::transparent);

    brushNULL.setColor(Qt::transparent);
    brushNULL.setStyle(Qt::SolidPattern);

    //definition of background texture ( german flag picture)
    brushMainMenuTexture.setTexture(QPixmap(":/graphics/graphics/mainMenu.jpg"));
    brushMainMenuTexture.texture().scaled(QSize(1200,600),Qt::IgnoreAspectRatio);
}

void Apperiance::definePen()
{
    //definition of pen to write
    blackPen.setColor(Qt::black);
    blackPen.setStyle(Qt::SolidLine);
}

void Apperiance::defineFont()
{
    //definition of used fonts of texts
    fontComicSans.setFamily("comic sans");
    fontComicSans.setPointSizeF(20);

    fontComicSans_15.setFamily("comic sans");
    fontComicSans_15.setPointSizeF(15);

    fontComicSans_13.setFamily("comic sans");
    fontComicSans_13.setPointSizeF(13);
}

void Apperiance::definePalette()
{
    //definition of palette
    paletteTransparent.setColor(QPalette::Base, Qt::transparent);
}

void Apperiance::definePixmap()
{
    //definition of pixmap with german flag picture
    pixmapHintImage.load(":/graphics/graphics/articles.jpg");
}

//GETTERS

QBrush Apperiance::getBrush(QBrush brushToGet){

    return brushToGet;
}




