//---------------------------------------------------------------------------
/*
QtLeftRightRectItem, QGraphicsRectItem with a left and right rectangle
Copyright (C) 2012  Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtleftrightrectitem.h"

#include <cassert>
#include <sstream>
//#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>

#pragma GCC diagnostic pop

ribi::QtLeftRightRectItem::QtLeftRightRectItem(QGraphicsItem* parent)
 : QGraphicsRectItem(parent),
   m_signal_request_scene_update{},
   m_focus(Focus::left)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->setRect(-16.0,-16.0,32.0,32.0);
}

const std::string ribi::QtLeftRightRectItem::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::QtLeftRightRectItem::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-12-19: version 1.0: initial version");
  v.push_back("2013-07-25: version 1.1: transition to Qt5");
  return v;
}

void ribi::QtLeftRightRectItem::keyPressEvent(QKeyEvent* event)
{
  switch (event->key())
  {
    case Qt::Key_F1:
    {
      m_focus = Focus::left;
      this->update();
      //m_signal_request_scene_update();
      //return;
    }
    break;
    case Qt::Key_F2:
    {
      {
        m_focus = Focus::right;
        this->update();
        //m_signal_request_scene_update();
        //return;
      }
    }
    break;
  }
  QGraphicsRectItem::keyPressEvent(event);

}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
void ribi::QtLeftRightRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  m_signal_request_scene_update();
  QGraphicsRectItem::mouseMoveEvent(event);
}
#pragma GCC diagnostic pop

void ribi::QtLeftRightRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* )
{

  //Always draw the outer rect
  if (this->hasFocus() || this->isSelected())
  {
    painter->setPen(QPen(Qt::DashLine));
  }
  painter->drawRect(rect());
  painter->setPen(QPen(Qt::SolidLine));


  const double hw = 0.5 * rect().width(); //Half-width
  QRectF rect_left  = rect().adjusted(   2.0,2.0,-hw-2.0,-2.0);
  QRectF rect_right = rect().adjusted(hw+2.0,2.0,   -2.0,-2.0);
  //The item can be selected by clicking on it
  //The item can have focus by moving towards it
  switch (m_focus)
  {
    case Focus::left:
    {
      painter->drawRect(rect_right);
      painter->setPen(QPen(QColor(255,0,0)));
      painter->drawRect(rect_left);
    }
    break;
    case Focus::right:
    {
      painter->drawRect(rect_left);
      painter->setPen(QPen(QColor(255,0,0)));
      painter->drawRect(rect_right);
    }
    break;
    default: assert(!"Should not get here");
  }
}
