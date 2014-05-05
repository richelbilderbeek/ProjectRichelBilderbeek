#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QGraphicsSvgItem i(":/images/CppQGraphicsSvgItemExample1.svg");
  i.setScale(0.25);

  QGraphicsScene s;
  s.addItem(&i);

  QGraphicsView w;
  w.setGeometry(100,100,200,200);
  w.setScene(&s);

  w.show();
  return a.exec();
}
