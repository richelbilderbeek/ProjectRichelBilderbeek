//---------------------------------------------------------------------------
/*
QtDisplayPosItem, QGraphicsItem that displays its position
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
//From http://www.richelbilderbeek.nl/CppQtDisplayPosItem.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtdisplaypositem.h"

#include <cassert>
#include <sstream>
//#include <QGraphicsScene>

QtDisplayPosItem::QtDisplayPosItem(QGraphicsItem *parent)
 : QGraphicsSimpleTextItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->update();
}

const std::string QtDisplayPosItem::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> QtDisplayPosItem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-19: version 1.0: initial version");
  v.push_back("2013-07-25: version 1.1: transition to Qt5");
  return v;
}

void QtDisplayPosItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  m_signal_request_scene_update();
  QGraphicsSimpleTextItem::mouseMoveEvent(event);
}

void QtDisplayPosItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  std::stringstream s;
  s << "(" << static_cast<int>(this->pos().x()) << "," << static_cast<int>(this->pos().y()) << ")";
  this->setText(s.str().c_str());
  QGraphicsSimpleTextItem::paint(painter,option,widget);
}
