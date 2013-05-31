#include <QtGui/QApplication>
#include "qtfilteroperationermaindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtFilterOperationerMainDialog w;
    w.show();
    
    return a.exec();
}
