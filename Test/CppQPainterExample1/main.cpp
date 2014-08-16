#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#pragma GCC diagnostic pop

int main( int argc, char* argv[])
{
  QApplication app( argc, argv );

  //Create a QPixmap to show
  QPixmap pixmap(256,256);
  pixmap.fill( Qt::white );

  //Create a QPainter to draw on the QPixmap
  QPainter painter(&pixmap);
  painter.setPen(Qt::black);

  //Wanted to tyy out some strange floating point values
  painter.drawEllipse(QPointF(126.6,126.4),124.1,123.3);

  //Create a QLabel to show the QPixmap
  QLabel label;
  label.setPixmap(pixmap);
  label.show();

  return app.exec();
}
