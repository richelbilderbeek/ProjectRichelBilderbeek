#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#pragma GCC diagnostic pop

struct QStringShower final : public QGraphicsSimpleTextItem
{
  QStringShower(const std::string& s = "")
  {
    setFlags(
        QGraphicsItem::ItemIsSelectable
      | QGraphicsItem::ItemIsMovable
    );
    SetString(s);
  }
  void SetString(const std::string s)
  {
    setText(s.c_str());
  }
};

void Test()
{
  QGraphicsScene scene;

  QStringShower item("Before");
  scene.addItem(&item);

  //Create an image of before
  QImage image_before(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
  {
    // Start all pixels transparent
    image_before.fill(Qt::transparent);
    QPainter painter(&image_before);
    scene.render(&painter);
    image_before.save("Before.png");
  }

  item.SetString("After");
  //Create an image of after
  QImage image_after(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
  {
    // Start all pixels transparent
    image_after.fill(Qt::transparent);
    QPainter painter(&image_after);
    scene.render(&painter);
    image_after.save("After.png");
  }

  //Assume both images differ
  assert(image_before != image_after);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Test();

  QGraphicsScene s;
  QStringShower t("QStringShower");

  s.addItem(&t);
  QGraphicsView v(&s);
  v.setGeometry(100,100,400,100);
  v.show();
  return a.exec();
}
