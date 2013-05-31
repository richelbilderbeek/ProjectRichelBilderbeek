#include <QtGui/QApplication>
#include "tooltestgraphicsproxywidgetmaindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolTestGraphicsProxyWidgetMainDialog w;
    w.show();
    
    return a.exec();
}
