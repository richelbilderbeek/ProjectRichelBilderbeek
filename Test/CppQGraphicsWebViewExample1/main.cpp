#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
//#include <QSvgWidget>
#include <QtWebKitWidgets/QGraphicsWebView>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsWebView w;

  //DOES NOT WORK

  w.setUrl(QUrl(":/images/CppQGraphicsWebViewExample1.svg"));
  w.show();
  return a.exec();
}
