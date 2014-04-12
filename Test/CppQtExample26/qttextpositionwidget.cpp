#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "qttextpositionitem.h"
#include "qttextpositionwidget.h"
#pragma GCC diagnostic pop

QtTextPositionWidget::QtTextPositionWidget(const std::vector<std::string>& items)
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  this->setScene(scene);

  std::for_each(items.begin(),items.end(),
    [this,scene](const std::string& s)
    {
      QtTextPositionItem * item = new QtTextPositionItem(s);
      //Scatter those items around a bit
      item->setPos(
        (this->width()  / 2.0) - 64 + (std::rand() % 128),
        (this->height() / 2.0) - 64 + (std::rand() % 128));

      scene->addItem(item);
    }
  );
}
