#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "qtpixelatormenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ribi::QtPixelatorMenuDialog w;
    w.show();
    return a.exec();
}
