//---------------------------------------------------------------------------
/*
QtKeyboardFriendlyGraphicsView, an keyboard friendly QGraphicsView
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtkeyboardfriendlygraphicsview.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>

//#include "conceptmaphelper.h"
#pragma GCC diagnostic pop

ribi::QtKeyboardFriendlyGraphicsView::QtKeyboardFriendlyGraphicsView(QWidget* parent)
  : QGraphicsView(new QGraphicsScene,parent),
    m_signal_update{}
{

}

QGraphicsItem* ribi::QtKeyboardFriendlyGraphicsView::GetClosest(
  const QGraphicsItem* const focus_item,
  const std::vector<QGraphicsItem *>& items) const
{
  assert(!items.empty());
  assert(std::count(items.begin(),items.end(),focus_item) == 0);

  QGraphicsItem* best = nullptr;
  double best_distance = std::numeric_limits<double>::max();
  for (QGraphicsItem* const item:items)
  {
    if (!(item->flags() & QGraphicsItem::ItemIsFocusable)) continue;
    if (!(item->isVisible())) continue;

    assert(item != focus_item);
    const double distance = GetDistance(focus_item->pos(),item->pos());
    if (distance < best_distance)
    {
      best_distance = distance;
      best = item;
    }
  }
  return best; //best can be nullptr
}

double ribi::QtKeyboardFriendlyGraphicsView::GetDistance(const QPointF& a, const QPointF& b)
{
  const double dx = a.x() - b.x();
  const double dy = a.y() - b.y();
  return std::sqrt((dx * dx) + (dy * dy));
}

std::vector<QGraphicsItem *> ribi::QtKeyboardFriendlyGraphicsView::GetItemsAbove(const QGraphicsItem* const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  //Look for items between North-West and North-East first
  for(QGraphicsItem* const item: items)
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
  if (!v.empty()) return v;
  //Look for items North (from West, through North, through East)
  for(QGraphicsItem* const item: items)
  {
    const double dy = item->pos().y() - focus_item->pos().y();
    if (dy < 0.0)  //Use '<' (instead of '<=') to leave out focus_item
    {
      assert(item != focus_item);
      v.push_back(item);
    }
  }
  return v;
}

std::vector<QGraphicsItem *> ribi::QtKeyboardFriendlyGraphicsView::GetItemsBelow(const QGraphicsItem* const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  //Look for items between South-East and South-West first
  for(QGraphicsItem* const item: items)
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
  if (!v.empty()) return v;
  //Look for items South
  for(QGraphicsItem* const item: items)
  {
    const double dy = item->pos().y() - focus_item->pos().y();
    if (dy > 0.0)  //Use '>' (instead of '>=') to leave out focus_item
    {
      assert(item != focus_item);
      v.push_back(item);
    }
  }
  return v;
}

std::vector<QGraphicsItem *> ribi::QtKeyboardFriendlyGraphicsView::GetItemsLeft(const QGraphicsItem* const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  //Look for items between South-West and North-West first
  for(QGraphicsItem* const item: items)
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
  //Look for items Westwards
  for(QGraphicsItem* const item: items)
  {
    const double dx = item->pos().x() - focus_item->pos().x();
    if (dx < 0.0)  //Use '<' (instead of '<=') to leave out focus_item
    {
      assert(item != focus_item);
      v.push_back(item);
    }
  }
  return v;
}

std::vector<QGraphicsItem *> ribi::QtKeyboardFriendlyGraphicsView::GetItemsRight(const QGraphicsItem* const focus_item) const
{
  std::vector<QGraphicsItem *> v;
  const QList<QGraphicsItem *> items = this->items();
  //Look for items between North-East and South-East first
  for(QGraphicsItem* const item: items)
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
  //Look for items Eastwards
  for(QGraphicsItem* const item: items)
  {
    const double dx = item->pos().x() - focus_item->pos().x();
    if (dx > 0.0) //Use '>' (instead of '>=') to leave out focus_item
    {
      assert(item != focus_item);
      v.push_back(item);
    }
  }
  return v;
}

std::string ribi::QtKeyboardFriendlyGraphicsView::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::QtKeyboardFriendlyGraphicsView::GetVersionHistory() noexcept
{
  return {
    "2012-12-13: version 1.0: initial version",
    "2012-12-31: version 1.1: improved moving focus",
    "2015-08-24: version 1.2: move item with CTRL, add selected with SHIFT, can move multiple items"
  };
}

void ribi::QtKeyboardFriendlyGraphicsView::keyPressEvent(QKeyEvent *event) noexcept
{
  //Move items
  if (event->modifiers() & Qt::ControlModifier)
  {
    double delta_x{0.0};
    double delta_y{0.0};
    switch (event->key())
    {
      case Qt::Key_Up   : delta_y = -10.0; break;
      case Qt::Key_Right: delta_x =  10.0; break;
      case Qt::Key_Down : delta_y =  10.0; break;
      case Qt::Key_Left : delta_x = -10.0; break;
    }
    for (const auto item: scene()->selectedItems())
    {
      assert(item);
      if (!(item->flags() & QGraphicsItem::ItemIsMovable)) { continue; }
      item->setPos(item->pos() + QPointF(delta_x,delta_y));
      m_signal_update(item);
    }
    scene()->update();
    return;

  }

  switch (event->key())
  {
    case Qt::Key_Up:
    {
      QGraphicsItem* const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsAbove(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem* const new_focus_item = GetClosest(focus_item,items);
      if (!new_focus_item) return;
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      if (event->modifiers() & Qt::ShiftModifier)
      {
        focus_item->setSelected(true);
        new_focus_item->setSelected(true);
      }
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Tab:
    case Qt::Key_Right:
    {
      QGraphicsItem* const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsRight(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem* const new_focus_item = GetClosest(focus_item,items);
      if (!new_focus_item) return;
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      if (event->modifiers() & Qt::ShiftModifier)
      {
        focus_item->setSelected(true);
        new_focus_item->setSelected(true);
      }
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Down:
    {
      QGraphicsItem* const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsBelow(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem* const new_focus_item = GetClosest(focus_item,items);
      if (!new_focus_item) return;
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      if (event->modifiers() & Qt::ShiftModifier)
      {
        focus_item->setSelected(true);
        new_focus_item->setSelected(true);
      }
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Left:
    case Qt::Key_Backtab:
    {
      QGraphicsItem* const focus_item = scene()->focusItem();
      if (!focus_item) { return; }
      const std::vector<QGraphicsItem *> items = GetItemsLeft(focus_item);
      if (items.empty()) { return; }
      QGraphicsItem* const new_focus_item = GetClosest(focus_item,items);
      if (!new_focus_item) return;
      focus_item->setEnabled(false);
      focus_item->clearFocus();
      focus_item->setEnabled(true);
      if (event->modifiers() & Qt::ShiftModifier)
      {
        focus_item->setSelected(true);
        new_focus_item->setSelected(true);
      }
      new_focus_item->setFocus();
    }
    break;
    case Qt::Key_Space:
    {
      SetRandomFocus();
    }
    break;
    case Qt::Key_Question:
    {
      if (const QGraphicsItem* const item = scene()->focusItem())
      {
        std::clog << __func__ << ": QGraphicsItem selected at ("
          << item->pos().x() << ","
          << item->pos().y() << ")"
          << std::endl;
      }
      else
      {
        std::clog << __func__ << ": no QGraphicsItem selected" << std::endl;
      }
    }
    break;
  }

  //Let QGraphicsView do the rest...
  QGraphicsView::keyPressEvent(event);
  this->update();
}

void ribi::QtKeyboardFriendlyGraphicsView::SetRandomFocus()
{
  //Let existing item lose focus
  if (QGraphicsItem* const item = scene()->focusItem())
  {
    //Really lose focus
    item->setEnabled(false);
    item->clearFocus();
    //item->setSelected(false); // #239
    item->setEnabled(true);
  }
  //Let a random item receive focus
  const QList<QGraphicsItem *> all_items = this->items();
  QList<QGraphicsItem *> items;
  std::copy_if(all_items.begin(),all_items.end(),std::back_inserter(items),
    [](const QGraphicsItem* const item)
    {
      return (item->flags() & QGraphicsItem::ItemIsFocusable)
        && item->isVisible();
    }
  );

  if (!items.empty())
  {
    const int i = std::rand() % items.size();
    items.at(i)->setFocus();
    //items.at(i)->setSelected(true); // #239
  }
}
