#include "mainwindow.h"
#include "carouselwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarouselWindow w;
    w.addImage(":/Resources/1.jpg");
    w.addImage(":/Resources/2.jpg");
    w.addImage(":/Resources/3.jpg");
    w.addImage(":/Resources/4.jpg");
    w.addImage(":/Resources/5.jpg");
    w.addImage(":/Resources/6.jpg");
    w.addImage(":/Resources/7.jpg");
    w.addImage(":/Resources/8.jpg");
    w.setButtonColor(Qt::yellow);
//    w.setButtonVisible(true);
    w.show();
    w.startPlay();
    return a.exec();
}
