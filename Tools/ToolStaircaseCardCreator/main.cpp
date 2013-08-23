#include <QApplication>
#include "dialogmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogMenu w;
    w.show();

    return a.exec();
}
