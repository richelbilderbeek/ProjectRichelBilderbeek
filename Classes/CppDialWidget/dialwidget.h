//---------------------------------------------------------------------------
/*
DialWidget, class for displaying a Dial
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDialWidget.htm
//---------------------------------------------------------------------------
#ifndef DIALWIDGET_H
#define DIALWIDGET_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include "widget.h"

namespace ribi {

struct Dial;

///DialWidget is a class to display a Dial
struct DialWidget : public Widget
{
  explicit DialWidget(
    const double position = 0.0,
    const int x = 0,
    const int y = 0,
    const int width = 100,
    const int height = 100,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Click on the Dial
  void Click(const int x, const int y);

  ///Obtain a read-and-write pointert to the Dial
  Dial * GetDial() { return m_dial.get(); }

  ///Obtain a read-only pointert to the Dial
  const Dial * GetDial() const { return m_dial.get(); }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Is the dial clicked?
  bool IsClicked(const int x, const int y) const;

  private:

  ///Test this class
  static void Test();

  //DialWidget can only be deleted by Boost smart pointers
  virtual ~DialWidget() {}
  friend void boost::checked_delete<>(DialWidget*);

  boost::scoped_ptr<Dial> m_dial;

  friend std::ostream& operator<<(std::ostream& os, const DialWidget& widget);

  public:

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);
  static double GetDistance(const double dx, const double dy);
};

std::ostream& operator<<(std::ostream& os, const DialWidget& widget);

} //~namespace ribi

#endif // DIALWIDGET_H
