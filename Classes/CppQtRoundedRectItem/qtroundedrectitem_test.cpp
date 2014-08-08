//---------------------------------------------------------------------------
/*
QtRoundedRectItem, rectangular-shaped QGraphicsItem
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
//From http://www.richelbilderbeek.nl/CppQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtroundedrectitem.h"

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::QtRoundedRectItem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Construction"); }
  {
    QtRoundedRectItem();
  }
  QtRoundedRectItem i;
  if (verbose) { TRACE("SetOuterX and GetOuterX must be symmetric"); }
  {
    const auto old_x = i.GetOuterX();
    const auto new_x = old_x + 10.0;
    i.SetOuterX(new_x);
    assert(std::abs(i.GetOuterX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("SetOuterY and GetOuterY must be symmetric"); }
  {
    const auto old_y = i.GetOuterY();
    const auto new_y = old_y + 10.0;
    i.SetOuterY(new_y);
    assert(std::abs(i.GetOuterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("SetOuterPos and GetOuterPos must be symmetric"); }
  {
    const auto old_pos = i.GetOuterPos();
    const auto new_pos = old_pos + QPointF(10.0,10.0);
    i.SetOuterPos(new_pos);
    assert(std::abs(i.GetOuterPos().x() - new_pos.x()) < 2.0);
    assert(std::abs(i.GetOuterPos().y() - new_pos.y()) < 2.0);
  }
  if (verbose) { TRACE("SetOuterWidth and GetOuterWidth must be symmetric"); }
  {
    const auto old_width = i.GetOuterWidth();
    const auto new_width = old_width + 10.0;
    i.SetOuterWidth(new_width);
    assert(std::abs(i.GetOuterWidth() - new_width) < 2.0);
  }
  if (verbose) { TRACE("SetOuterHeight and GetOuterHeight must be symmetric"); }
  {
    const auto old_height = i.GetOuterHeight();
    const auto new_height = old_height + 10.0;
    i.SetOuterHeight(new_height);
    assert(std::abs(i.GetOuterHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("SetInnerX and GetInnerX must be symmetric"); }
  {
    const auto old_x = i.GetInnerX();
    const auto new_x = old_x + 10.0;
    i.SetInnerX(new_x);
    assert(std::abs(i.GetInnerX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("SetInnerY and GetInnerY must be symmetric"); }
  {
    const auto old_y = i.GetInnerY();
    const auto new_y = old_y + 10.0;
    i.SetInnerY(new_y);
    assert(std::abs(i.GetInnerY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("SetInnerPos and GetInnerPos must be symmetric"); }
  {
    const auto old_pos = i.GetInnerPos();
    const auto new_pos = old_pos + QPointF(10.0,10.0);
    i.SetInnerPos(new_pos);
    assert(std::abs(i.GetInnerPos().x() - new_pos.x()) < 2.0);
    assert(std::abs(i.GetInnerPos().y() - new_pos.y()) < 2.0);
  }
  if (verbose) { TRACE("SetInnerHeight and GetInnerHeight must be symmetric"); }
  {
    const auto old_height = i.GetInnerHeight();
    const auto new_height = old_height + 10.0;
    i.SetInnerHeight(new_height);
    assert(std::abs(i.GetInnerHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("SetInnerWidth and GetInnerWidth must be symmetric"); }
  {
    const auto old_width = i.GetInnerWidth();
    const auto new_width = old_width + 10.0;
    i.SetInnerWidth(new_width);
    //Difference has been measured to be 3.0
    assert(std::abs(i.GetInnerWidth() - new_width) < 4.0);
  }
  if (verbose) { TRACE("SetRadiusX and GetRadiusX must be symmetric"); }
  {
    const auto old_radius_x = i.GetRadiusX();
    const auto new_radius_x = old_radius_x + 10.0;
    i.SetRadiusX(new_radius_x);
    assert(std::abs(i.GetRadiusX() - new_radius_x) < 2.0);
  }
  if (verbose) { TRACE("SetRadiusY and GetRadiusY must be symmetric"); }
  {
    const auto old_radius_y = i.GetRadiusY();
    const auto new_radius_y = old_radius_y + 10.0;
    i.SetRadiusY(new_radius_y);
    assert(std::abs(i.GetRadiusY() - new_radius_y) < 2.0);
  }
  if (verbose) { TRACE("Position must be in GetOuterRect"); }
  {
    assert(i.GetOuterRect().contains(i.GetOuterPos()));
  }
  if (verbose) { TRACE("Position must be in GetInnerRect"); }
  {
    assert(i.GetInnerRect().contains(i.GetInnerPos()));
  }
  if (verbose) { TRACE("After changing the outer width and position, the Position must be in GetOuterRect"); }
  {
    i.SetOuterWidth(3.0);
    i.SetOuterHeight(3.0);
    i.SetOuterX(i.GetInnerX() + 10.0);
    i.SetOuterY(i.GetInnerY() + 10.0);
    assert(i.GetOuterRect().contains(i.GetOuterPos()));
  }
  if (verbose) { TRACE("After changing the inner width and position, the Position must be in GetInnerRect"); }
  {
    i.SetInnerWidth(3.0);
    i.SetInnerHeight(3.0);
    i.SetInnerX(i.GetInnerX() + 10.0);
    i.SetInnerY(i.GetInnerY() + 10.0);
    assert(i.GetInnerRect().contains(i.GetInnerPos()));
  }
}
#endif

