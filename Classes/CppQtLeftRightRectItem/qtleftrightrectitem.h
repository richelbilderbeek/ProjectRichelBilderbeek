//---------------------------------------------------------------------------
/*
QtLeftRightRectItem, QGraphicsRectItem with a left and right rectangle
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtLeftRightRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTLEFTRIGHTRECTITEM_H
#define QTLEFTRIGHTRECTITEM_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include <QGraphicsRectItem>
#pragma GCC diagnostic pop

namespace ribi {

///A rect item that has two focuses: left and right!
struct QtLeftRightRectItem : public QGraphicsRectItem
{
  QtLeftRightRectItem(QGraphicsItem* parent = 0);

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Signal to request a scene update, because this item has moved/changed
  boost::signals2::signal<void ()> m_signal_request_scene_update;

  private:
  ///Respond to key press
  void keyPressEvent(QKeyEvent *event);

  ///Respond to mouse move
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

  ///Paint this item
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

  enum class Focus { left, right } m_focus;
};

} //~namespace ribi

#endif // QTLEFTRIGHTRECTITEM_H
