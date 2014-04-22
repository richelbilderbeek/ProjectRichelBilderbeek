#include "qtwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/math/constants/constants.hpp>

#include <QGraphicsScene>
#include <QKeyEvent>
#include "qttextitem.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  const int n_items = 16;
  for (int i=0; i!=n_items; ++i)
  {
    const double tau = boost::math::constants::two_pi<double>();
    const double angle = tau * (static_cast<double>(i+0) / static_cast<double>(n_items));
    const double ray = 150.0;
    const double x =  std::sin(angle) * ray;
    const double y = -std::cos(angle) * ray;

    QtTextItem * const item = new QtTextItem;
    item->setPos(x,y);
    scene()->addItem(item);
  }
  {

    QGraphicsSimpleTextItem * const item = new QGraphicsSimpleTextItem;
    item->setText("Shift: Select additional items");
    item->setPos(-30.0,-10.0);
    scene()->addItem(item);

  }
  {
    QGraphicsSimpleTextItem * const item = new QGraphicsSimpleTextItem;
    item->setText("Control: Move selected items");
    item->setPos(-30.0,10.0);
    scene()->addItem(item);

  }
}

QGraphicsItem * QtWidget::GetClosest(
  const QGraphicsItem * const focus_item,
  const std::vector<QGraphicsItem *>& items) const
{
  assert(!items.empty());
  //Remove focus item for items_all (if needed)
  //std::vector<QGraphicsItem *> items(items_all);
  //items.erase(std::remove(items.begin(),items.end(),focus_item),items.end());
  assert(std::count(items.begin(),items.end(),focus_item) == 0);

  QGraphicsItem * best = nullptr;
  double best_distance = std::numeric_limits<double>::max();
  for (QGraphicsItem * const item:items)
  {
    assert(item != focus_item);
    const double distance = GetDistance(focus_item->pos(),item->pos());
    if (distance < best_distance)
    {
      best_distance = distance;
      best = item;
    }
  }
  assert(best);
  return best;
}

double QtWidget::GetDistance(const QPointF& a, const QPointF& b)
{
  const double dx = a.x() - b.x();
  const double dy = a.y() - b.y();
  return std::sqrt((dx * dx) + (dy * dy));
}

const std::vector<QGraphicsItem *> QtWidget::GetItemsAbove(const QGraphicsItem * const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  for(QGraphicsItem * const item: items)
  {
    const double dy = item->pos().y() - focus_item->pos().y();
    if (dy < 0.0)  //Use '<' (instead of '<=') to leave out focus_item
    {
      const double dx = item->pos().x() - focus_item->pos().x();
      if (std::abs(dx) < std::abs(dy))
      {
        assert(item != focus_item);
        v.push_back(item);
      }
    }
  }
  return v;
}

const std::vector<QGraphicsItem *> QtWidget::GetItemsBelow(const QGraphicsItem * const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  for(QGraphicsItem * const item: items)
  {
    const double dy = item->pos().y() - focus_item->pos().y();
    if (dy > 0.0)  //Use '>' (instead of '>=') to leave out focus_item
    {
      const double dx = item->pos().x() - focus_item->pos().x();
      if (std::abs(dx) < std::abs(dy))
      {
        assert(item != focus_item);
        v.push_back(item);
      }
    }
  }
  return v;
}

const std::vector<QGraphicsItem *> QtWidget::GetItemsLeft(const QGraphicsItem * const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  for(QGraphicsItem * const item: items)
  {
    const double dx = item->pos().x() - focus_item->pos().x();
    if (dx < 0.0)  //Use '<' (instead of '<=') to leave out focus_item
    {
      const double dy = item->pos().y() - focus_item->pos().y();
      if (std::abs(dy) < std::abs(dx))
      {
        assert(item != focus_item);
        v.push_back(item);
      }
    }
  }
  return v;
}

const std::vector<QGraphicsItem *> QtWidget::GetItemsRight(const QGraphicsItem * const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  for(QGraphicsItem * const item: items)
  {
    const double dx = item->pos().x() - focus_item->pos().x();
    if (dx > 0.0) //Use '>' (instead of '>=') to leave out focus_item
    {
      const double dy = item->pos().y() - focus_item->pos().y();
      if (std::abs(dy) < std::abs(dx))
      {
        assert(item != focus_item);
        v.push_back(item);
      }
    }
  }
  return v;
}


void QtWidget::keyPressEvent(QKeyEvent *event)
{
  const auto key(event->key());
  std::function<std::vector<QGraphicsItem *>(QtWidget *, const QGraphicsItem * const focus_item)> f;

  switch (key)
  {
    case Qt::Key_Up   : f = &QtWidget::GetItemsAbove; break;
    case Qt::Key_Right: f = &QtWidget::GetItemsRight; break;
    case Qt::Key_Down : f = &QtWidget::GetItemsBelow; break;
    case Qt::Key_Left : f = &QtWidget::GetItemsLeft ; break;
  }

  if (event->modifiers() & Qt::ShiftModifier)
  {
    switch (key)
    {
      case Qt::Key_Right:
      case Qt::Key_Up:
      case Qt::Key_Down:
      case Qt::Key_Left:
      {
        QGraphicsItem * const focus_item = scene()->focusItem();
        if (!focus_item) { return; }
        const std::vector<QGraphicsItem *> items = f(this,focus_item);
        if (items.empty()) { return; }
        QGraphicsItem * const new_focus_item = GetClosest(focus_item,items);
        new_focus_item->setSelected(true);
      }
      break;
      case Qt::Key_Space:
      {
        SetRandomSelect();
      }
    }
  }
  else if (event->modifiers() & Qt::ControlModifier)
  {
    double dx = 0.0;
    double dy = 0.0;
    const double d = 10.0;
    switch (key)
    {
      case Qt::Key_Right: dx =  d; break;
      case Qt::Key_Up   : dy = -d; break;
      case Qt::Key_Down : dy =  d; break;
      case Qt::Key_Left : dx = -d; break;
    }

    switch (key)
    {
      case Qt::Key_Right:
      case Qt::Key_Up:
      case Qt::Key_Down:
      case Qt::Key_Left:
      {
        auto items(scene()->selectedItems());
        if (scene()->focusItem()) items.push_back(scene()->focusItem());
        for (auto item: items) item->moveBy(dx,dy);
      }
      break;
    }
  }
  //Let QGraphicsView do the rest...
  QGraphicsView::keyPressEvent(event);
}


void QtWidget::SetRandomFocus()
{
  //Let existing item lose focus
  if (QGraphicsItem * const item = scene()->focusItem())
  {
    //Really lose focus
    item->setEnabled(false);
    item->clearFocus();
    item->setEnabled(true);
  }
  //Let a random item receive focus
  const QList<QGraphicsItem *> items = this->items();
  items.at( std::rand() % items.size() )->setFocus();
}

void QtWidget::SetRandomSelect()
{
  //Let a random item receive select
  const QList<QGraphicsItem *> items = this->items();
  items.at( std::rand() % items.size() )->setSelected(true);
}
