//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapitemhighlighter.h"

#include <boost/math/constants/constants.hpp>

#include <QGraphicsItem>
#include <QTimer>
//#include "qtconceptmapconceptitem.h"
#include "qtconceptmapnode.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtItemHighlighter::QtItemHighlighter(QObject *parent)
  : QObject(parent),
    m_cnt(0),
    m_item(nullptr),
    m_timer(new QTimer(this))
{
  m_timer->setInterval(10); //ms
  QObject::connect(
    m_timer,
    &QTimer::timeout,
    this,
    &ribi::cmap::QtItemHighlighter::OnTimer
  );
}

void ribi::cmap::QtItemHighlighter::SetItem(QtNode* const item)
{
  if (m_item == item) return;

  if (item)
  {
    this->m_timer->start();
  }
  else
  {
    ///Set the current item in its normal rotation
    if (m_item) m_item->setRotation(0.0);
    this->m_timer->stop();
  }
  m_item = item;
}


void ribi::cmap::QtItemHighlighter::OnTimer()
{
  if (m_item)
  {
    ++m_cnt;
    #define USE_ROTATION_ANIMATION_675982734653425297529
    #ifdef USE_MOVING_POSITION_ANIMATION_723497235973450873659360843975308
    QPointF pos = m_item->pos();
    switch (m_cnt % 4)
    {
      case 0: pos.setX(pos.x() + 2.0); break;
      case 1: pos.setY(pos.y() + 2.0); break;
      case 2: pos.setX(pos.x() - 2.0); break;
      case 3: pos.setY(pos.y() - 2.0); break;
      default: assert(!"Should not get here");
    }
    m_item->setPos(pos);
    #endif
    #ifdef USE_ROTATION_ANIMATION_675982734653425297529
    const double pi = boost::math::constants::pi<double>();
    const double angle = 2.0 * pi * static_cast<double>(m_cnt) / 360.0;
    const double speed_up = 5.0;
    const double r = std::sin(angle * speed_up) * 5.0;
    m_item->setRotation(r);
    #endif
    m_item->update();
  }
}
