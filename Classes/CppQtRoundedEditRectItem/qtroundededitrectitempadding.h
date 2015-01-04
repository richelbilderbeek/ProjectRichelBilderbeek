//---------------------------------------------------------------------------
/*
QtRoundedEditRectItem, editable rectangular-shaped QGraphicsItem
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
//From http://www.richelbilderbeek.nl/QtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTROUNDEDEDITRECTITEMPADDING_H
#define QTROUNDEDEDITRECTITEMPADDING_H

#include <iosfwd>

namespace ribi {

struct QtRoundedEditRectItemPadding
{
  QtRoundedEditRectItemPadding(
    const double any_top = 0.0,
    const double any_right = 0.0,
    const double any_bottom = 0.0,
    const double any_left = 0.0
  )
    : bottom(any_bottom), left(any_left), right(any_right), top(any_top) {}
  double bottom;
  double left;
  double right;
  double top;
};

std::ostream& operator<<(std::ostream& os, const QtRoundedEditRectItemPadding &p) noexcept;
bool operator==(const QtRoundedEditRectItemPadding& lhs, const QtRoundedEditRectItemPadding& rhs) noexcept;
bool operator!=(const QtRoundedEditRectItemPadding& lhs, const QtRoundedEditRectItemPadding& rhs) noexcept;

} //~namespace ribi

#endif // QTROUNDEDEDITRECTITEMPADDING_H
