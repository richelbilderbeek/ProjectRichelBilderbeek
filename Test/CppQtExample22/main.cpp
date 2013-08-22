#include <QtGui/QApplication>
#include "transparentdialog.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransparentDialog w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif
    return a.exec();
}
//---------------------------------------------------------------------------
