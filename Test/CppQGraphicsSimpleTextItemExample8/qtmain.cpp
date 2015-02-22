#include <cassert>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

struct MyBoundedTextItem : public QGraphicsSimpleTextItem
{
  MyBoundedTextItem(const std::string& s)
  {
    this->setText(s.c_str());
  }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
  {
    QGraphicsSimpleTextItem::paint(painter,option,widget);
    painter->setBrush(QBrush(QColor(0,0,0,0)));
    painter->drawRect(this->boundingRect().adjusted(1.0,1.0,-1.0,-1.0));
  }
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QGraphicsScene scene;
  QGraphicsView view(&scene);
  view.setGeometry(0,28,480,100);

  MyBoundedTextItem item("CppQGraphicsSimpleTextItemExample8");
  item.setFlags(
      QGraphicsItem::ItemIsSelectable
    | QGraphicsItem::ItemIsFocusable
  );

  scene.addItem(&item);
  view.show();
  return a.exec();
}
