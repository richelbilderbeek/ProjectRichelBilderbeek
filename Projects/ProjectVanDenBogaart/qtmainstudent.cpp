#include <QtGui/QApplication>
#include "qtstudentmenudialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtStudentMenuDialog w;
    w.show();
    
    return a.exec();
}
