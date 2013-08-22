#include <QtGui/QApplication>
#include "tooltesttextpositionwidgetdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolTestTextPositionWidgetDialog w;
    w.show();
    
    return a.exec();
}
