#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <memory>

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  const std::shared_ptr<QGraphicsItem> item{
    std::make_shared<QGraphicsSimpleTextItem>("CppQGraphicsItemExample1")
  };

  QGraphicsScene s;
  s.addItem(item.get());

  QGraphicsView w;
  w.setGeometry(100,100,400,100);
  w.setScene(&s);

  //item->dragEnterEvent(nullptr); //protected
  //item->dragMoveEvent(nullptr);  //protected
  //item->dragLeaveEvent(nullptr); //protected

  w.show();
  a.exec();

  //Prevent QGraphicsScene from deleting item (let item be deleted by std::shared_ptr instead)
  s.removeItem(item.get());
}
