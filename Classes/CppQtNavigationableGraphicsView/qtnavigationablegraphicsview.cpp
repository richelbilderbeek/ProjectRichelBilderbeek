//---------------------------------------------------------------------------
/*
QtNavigationableGraphicsView, navigationable QGraphicsView
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtNavigationableGraphicsView.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtnavigationablegraphicsview.h"

#include <QGraphicsScene>
#include <QWheelEvent>
#pragma GCC diagnostic pop


ribi::QtNavigationableGraphicsView::QtNavigationableGraphicsView(QWidget *parent)
  : QGraphicsView(parent)
{
  QGraphicsScene * const s = new QGraphicsScene(this);
  this->setScene(s);
}

void ribi::QtNavigationableGraphicsView::wheelEvent(QWheelEvent *event)
{
  const double new_scale = 1.0 + (static_cast<double>(event->delta()) / 1000.0);
  this->scale(new_scale,new_scale);
}
