#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "qtfunctionplottermenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ribi::QtFunctionPlotterMenuDialog w;
    w.show();
    
    return a.exec();
}
