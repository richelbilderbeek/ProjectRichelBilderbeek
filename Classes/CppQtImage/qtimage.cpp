#include "qtimage.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtImage::QtImage() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif // NDEBUG
}

QImage ribi::QtImage::Difference(const QImage& base, const QImage& to_xor) noexcept
{
  QImage result{base};
  {
    QPainter painter(&result);
    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    painter.drawImage(0,0,to_xor);
  }
  return result;
}

std::string ribi::QtImage::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtImage::GetVersionHistory() noexcept
{
  return {
    "2014-08-05: Version 1.0: initial version",
  };
}

QImage ribi::QtImage::Paint(const QGraphicsItem& item) noexcept
{
  if (item.scene())
  {
    auto& scene = *item.scene();
    // Create the image with the exact size of the shrunk scene
    const QSize old_size{scene.sceneRect().size().toSize()};
    //Rescaled by a factor two to fix BUG_260
    //const QSize new_size(old_size.scaled(2,2, Qt::KeepAspectRatio));
    QImage image(old_size, QImage::Format_ARGB32);
    // Start all pixels transparent
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene.render(&painter);
    return image;
  }
  else
  {
    QGraphicsScene scene;
    scene.addItem(&const_cast<QGraphicsItem&>(item)); //Temporarily add the item, won't modify it

    const QSize old_size{scene.sceneRect().size().toSize()};
    //Rescaled by a factor two to fix BUG_260
    //const QSize new_size(old_size.scaled(2,2, Qt::KeepAspectRatio));
    QImage image(old_size, QImage::Format_ARGB32);
    // Start all pixels transparent
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene.render(&painter);
    scene.removeItem(&const_cast<QGraphicsItem&>(item)); //Prevent item being deleted
    return image;
  }
}


#ifndef NDEBUG
void ribi::QtImage::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Default-construction of QtImage"); }
  {
    const QtImage q;
  }
  if (verbose) { TRACE("QImage pixel manipultion"); }
  {
    QImage q(1,1,QImage::Format_RGB32);
    q.setPixel(0,0,qRgb(1,2,3));
    assert(q.pixel(0,0) == qRgb(1,2,3));
  }
  if (verbose) { TRACE("QGraphicsItem rendering"); }
  {
    QGraphicsSimpleTextItem item;
    item.setText(__func__);
    QImage image{QtImage().Paint(item)};
    assert(image.width() > 1);
    assert(image.height() > 1);
    image.save("tmp_ribi_QtImage_Test.png");
  }
}
#endif

QImage ribi::QtImage::Xor(const QImage& base, const QImage& to_xor) noexcept
{
  QImage result{base};
  {
    QPainter painter(&result);
    //painter.setCompositionMode(QPainter::CompositionMode_Xor);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.drawImage(0,0,to_xor);
  }
  return result;
}

