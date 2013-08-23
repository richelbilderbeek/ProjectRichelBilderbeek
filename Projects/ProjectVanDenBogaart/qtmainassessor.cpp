#include <QApplication>
#include "qtassessormenudialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtAssessorMenuDialog w;
    w.show();
    
    return a.exec();
}
