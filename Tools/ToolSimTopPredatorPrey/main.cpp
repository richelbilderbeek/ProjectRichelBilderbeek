#include "qtsimtoppredatorpraymaindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSimTopPredatorPrayMainDialog w;
    w.show();

    return a.exec();
}
