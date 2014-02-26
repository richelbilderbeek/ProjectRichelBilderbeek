#include <QApplication>
#include "dialogmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogMenu w;
    w.show();

    return a.exec();
}

/*

* YYYY-MM-DD: version X.Y: [description]
* 2009-01-11: version 1.0: initial version developed under C++ Builder, supporting Windows only, supports the bitmap graphic format only
* 2010-10-19: version 1.1: port to Qt Creator, supporting more operating systems, added support for any graphic format

*/
