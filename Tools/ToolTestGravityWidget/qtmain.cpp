#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include "tooltestgravitywidgetmaindialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolTestGravityWidgetMainDialog w;
    w.show();
    return a.exec();
}
