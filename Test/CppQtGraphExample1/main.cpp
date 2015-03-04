// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#include <QApplication>

#include "graphwidget.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  GraphWidget * const widget{new GraphWidget};
  widget->show();
  return app.exec();
}
