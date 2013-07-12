
/*
RubiksClockDialWidget, class for displaying a RubiksClockDial
Copyright (C) 2011 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/CppRubiksClockDialWidget.htm

#ifndef RUBIKSCLOCKDIALWIDGET_H
#define RUBIKSCLOCKDIALWIDGET_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include "widget.h"

struct RubiksClockDial;

///RubiksClockDialWidget is a class to display a RubiksClockDial
struct RubiksClockDialWidget : public Widget
{
  explicit RubiksClockDialWidget(
    const double position,
    const int x,
    const int y,
    const int width,
    const int height,
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue);

  ///Obtain a read-and-write pointert to the RubiksClockDial
  RubiksClockDial * GetRubiksClockDial() { return m_dial.get(); }

  ///Obtain a read-only pointert to the RubiksClockDial
  const RubiksClockDial * GetRubiksClockDial() const { return m_dial.get(); }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Is the dial clicked?
  bool IsClicked(const int x, const int y) const;

  private:
  //RubiksClockDialWidget can only be deleted by Boost smart pointers
  virtual ~RubiksClockDialWidget() {}
  friend void boost::checked_delete<>(RubiksClockDialWidget*);

  boost::scoped_ptr<RubiksClockDial> m_dial;

  static double GetDistance(const double dX, const double dY);


  friend std::ostream& operator<<(std::ostream& os, const RubiksClockDialWidget& widget);
};

std::ostream& operator<<(std::ostream& os, const RubiksClockDialWidget& widget);

#endif // RUBIKSCLOCKDIALWIDGET_H
