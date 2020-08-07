#include "fractal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fractal w;
    w.show();
    return a.exec();
}
