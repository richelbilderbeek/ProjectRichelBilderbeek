//---------------------------------------------------------------------------
/*
QtDisplayPosItem, QGraphicsItem that displays its position
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
//From http://www.richelbilderbeek.nl/CppQtDisplayPosItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtdisplaypositem.h"

#include <cassert>
#include <sstream>
//#include <QGraphicsScene>

#pragma GCC diagnostic pop

ribi::QtDisplayPosItem::QtDisplayPosItem(QGraphicsItem *parent)
 : QGraphicsSimpleTextItem(parent),
   m_signal_request_scene_update{}
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->update();
}

std::string ribi::QtDisplayPosItem::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtDisplayPosItem::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-12-19: version 1.0: initial version");
  v.push_back("2013-07-25: version 1.1: transition to Qt5");
  return v;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
void ribi::QtDisplayPosItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  m_signal_request_scene_update();
  QGraphicsSimpleTextItem::mouseMoveEvent(event);
}
#pragma GCC diagnostic pop

void ribi::QtDisplayPosItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  std::stringstream s;
  s << "(" << static_cast<int>(this->pos().x()) << "," << static_cast<int>(this->pos().y()) << ")";
  this->setText(s.str().c_str());
  QGraphicsSimpleTextItem::paint(painter,option,widget);
}
