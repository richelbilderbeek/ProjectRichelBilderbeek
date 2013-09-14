//---------------------------------------------------------------------------
/*
QtKeyboardFriendlyGraphicsView, an keyboard friendly QGraphicsView
Copyright (C) 2012 Richel Bilderbeek

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
#ifndef QTKEYBOARDFRIENDLYGRAPHICSVIEW_H
#define QTKEYBOARDFRIENDLYGRAPHICSVIEW_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QGraphicsItem;

namespace ribi {

///The widget holding the items
struct QtKeyboardFriendlyGraphicsView : public QGraphicsView
{
  QtKeyboardFriendlyGraphicsView(QWidget* parent = 0);

  ///QtKeyboardFriendlyGraphicsView creates its own QGraphicsScene
  QtKeyboardFriendlyGraphicsView(QGraphicsScene* scene, QWidget* parent) = delete;

  virtual ~QtKeyboardFriendlyGraphicsView() {}

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Respond to a key press
  virtual void keyPressEvent(QKeyEvent *event);

  ///Signals which QGraphicsItem has been moved by setpos
  boost::signals2::signal<void (QGraphicsItem*)> m_signal_update;

  private:

  ///Obtain the closest item in the collection
  ///Returns nullptr if there is no focusable item in the items
  QGraphicsItem* GetClosest(
    const QGraphicsItem* const focus_item,
    const std::vector<QGraphicsItem *>& items) const;

  ///Calculate the Euclidian distance between two points
  static double GetDistance(const QPointF& a, const QPointF& b);

  ///Obtain the items above the focus_item
  const std::vector<QGraphicsItem *> GetItemsAbove(const QGraphicsItem* const focus_item) const;

  ///Obtain the items below the focus_item
  const std::vector<QGraphicsItem *> GetItemsBelow(const QGraphicsItem* const focus_item) const;

  ///Obtain the items left of the focus_item
  const std::vector<QGraphicsItem *> GetItemsLeft(const QGraphicsItem* const focus_item) const;

  ///Obtain the items right of the focus_item
  const std::vector<QGraphicsItem *> GetItemsRight(const QGraphicsItem* const focus_item) const;

  ///Give focus to a random item
  void SetRandomFocus();
};

} //~namespace ribi

#endif // QTKEYBOARDFRIENDLYGRAPHICSVIEW_H
