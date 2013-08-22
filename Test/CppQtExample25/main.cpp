#include <QtGui/QApplication>
#include "transparentsketchdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransparentSketchDialog w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
