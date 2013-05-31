#include <QtGui/QApplication>
#include "dialoggame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogGame w;
    w.show();

    return a.exec();
}
