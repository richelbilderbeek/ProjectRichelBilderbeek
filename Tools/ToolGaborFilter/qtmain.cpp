#include <QtGui/QApplication>
#include "qttoolgaborfiltermenudialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtToolGaborFilterMenuDialog w;
    w.show();
    
    return a.exec();
}
