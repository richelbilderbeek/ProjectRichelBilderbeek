#include <QApplication>
#include "tooltestgravitywidgetmaindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolTestGravityWidgetMainDialog w;
    w.show();
    
    return a.exec();
}
