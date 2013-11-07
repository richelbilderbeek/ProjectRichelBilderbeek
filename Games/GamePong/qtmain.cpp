#include <QApplication>
#include "pongmaindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PongMainDialog w;
    w.show();
    
    return a.exec();
}
