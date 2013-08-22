#include <cassert>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "qttextpositionwidget.h"

QtTextPositionWidget::QtTextPositionWidget(const std::vector<std::string>& items)
{
  QGraphicsScene * const scene = new QGraphicsScene(this);
  this->setScene(scene);

  std::for_each(items.begin(),items.end(),
    [this,scene](const std::string& s)
    {
      QGraphicsTextItem * item = new QGraphicsTextItem;
      item->setPlainText(s.c_str());
      item->setFlags(QGraphicsItem::ItemIsMovable);
      item->setPos(this->width() / 2.0, this->height() / 2.0);
      scene->addItem(item);
    }
  );
}
