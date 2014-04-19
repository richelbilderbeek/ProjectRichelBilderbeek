#include "qtwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include "qttextitem.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent)
{
  const int n_items = 16;
  for (int i=0; i!=n_items; ++i)
  {

    const double angle
      = boost::math::constants::two_pi<double>()
      * (static_cast<double>(i+0) / static_cast<double>(n_items));
    const double ray = 150.0;
    const double x =  std::sin(angle) * ray;
    const double y = -std::cos(angle) * ray;

    QtTextItem * const item = new QtTextItem;
    item->setPos(x,y);
    //item->setPos(QPointF(x,y)-item->boundingRect().center());
    scene()->addItem(item);
  }
  {
    QGraphicsSimpleTextItem * const item = new QGraphicsSimpleTextItem(
      "Arrow: move focus\n"
      "Shift + arrow: move item\n"
      "Space: go to random item"
      );
    item->setPos(this->mapToScene(40,40));
    item->setFlags(
        QGraphicsItem::ItemIsFocusable
      | QGraphicsItem::ItemIsMovable
      | QGraphicsItem::ItemIsSelectable);

    scene()->addItem(item);
  }
}

QGraphicsItem * QtWidget::GetClosest(
  const QGraphicsItem * const focus_item,
  const std::vector<QGraphicsItem *>& items) const
{
  assert(!items.empty());
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
  if (event->modifiers() & Qt::ShiftModifier)
  {
    switch (event->key())
    {
      case Qt::Key_Up:
      {
        QGraphicsItem * const focus_item = scene()->focusItem();
        if (!focus_item) { return; }
        focus_item->setPos(focus_item->pos() + QPointF(0.0,-10.0));
        return;
      }
      case Qt::Key_Right:
      {
        QGraphicsItem * const focus_item = scene()->focusItem();
        if (!focus_item) { return; }
        focus_item->setPos(focus_item->pos() + QPointF(10.0,0.0));
        return;
      }
      case Qt::Key_Down:
      {
        QGraphicsItem * const focus_item = scene()->focusItem();
        if (!focus_item) { return; }
        focus_item->setPos(focus_item->pos() + QPointF(0.0,10.0));
        return;
      }
      case Qt::Key_Left:
      {
        QGraphicsItem * const focus_item = scene()->focusItem();
        if (!focus_item) { return; }
        focus_item->setPos(focus_item->pos() + QPointF(-10.0,0.0));
        return;
      }
    }
  }

  switch (event->key())
  {
    case Qt::Key_Up:
    {
      QGraphicsItem * const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsAbove(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem * const new_focus_item = GetClosest(focus_item,items);
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Tab:
    case Qt::Key_Right:
    {
      QGraphicsItem * const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsRight(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem * const new_focus_item = GetClosest(focus_item,items);
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Down:
    {
      QGraphicsItem * const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsBelow(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem * const new_focus_item = GetClosest(focus_item,items);
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Left:
    case Qt::Key_Backtab:
    {
      QGraphicsItem * const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsLeft(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem * const new_focus_item = GetClosest(focus_item,items);
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Space:
    {
      SetRandomFocus();
    }
    break;
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
