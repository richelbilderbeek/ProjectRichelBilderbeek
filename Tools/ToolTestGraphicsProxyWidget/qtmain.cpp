#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include "tooltestgraphicsproxywidgetmaindialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolTestGraphicsProxyWidgetMainDialog w;
    w.show();
    
    return a.exec();
}
