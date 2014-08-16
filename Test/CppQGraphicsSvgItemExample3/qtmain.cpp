#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <fstream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include "mygraphicsview.h"
#pragma GCC diagnostic pop


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  const std::string filename = "tmp.svg";
  {
    std::ofstream f(filename.c_str());
    //Use '*(' and ')*' as delimiters
    f
      << R"*(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)*"
      << R"*(<rect width="150" height="150" fill="rgb(0, 255, 0)" stroke-width="1" stroke="rgb(0, 0, 0)" />)*"
      << R"*(</svg>)*";
  }
  QGraphicsSvgItem i(filename.c_str());

  i.setScale(0.25);

  QGraphicsScene s;
  s.addItem(&i);

  MyGraphicsView w;
  w.setGeometry(100,100,200,200);
  w.setScene(&s);

  w.show();
  return a.exec();
}
