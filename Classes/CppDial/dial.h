//---------------------------------------------------------------------------
/*
Dial, dial class
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
//From http://www.richelbilderbeek.nl/CppDial.htm
//---------------------------------------------------------------------------
#ifndef DIAL_H
#define DIAL_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
  #include <boost/checked_delete.hpp>
  #include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Dial is a class for a dial
struct Dial
{
  explicit Dial(const double position = 0.0,
    const unsigned char red   = 255,
    const unsigned char green = 255,
    const unsigned char blue  = 255);

  ///Get the blueness of the Dial its color
  unsigned char GetBlue() const { return m_blue; }

  ///Get the greenness of the Dial its color
  unsigned char GetGreen() const { return m_green; }

  ///\brief
  ///Get the position of the Dial
  ///
  ///0.00: Up   , 12:00 'o clock
  ///0.25: Right,  3:00 'o clock
  ///0.05: Down ,  6:00 'o clock
  ///0.75: Left ,  9:00 'o clock
  ///1.00: Up   , 12:00 'o clock
  double GetPosition() const { return m_position; }

  ///Get the redness of the Dial its color
  unsigned char GetRed() const { return m_red; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Set the blue the Dial
  void SetBlue(const int b);

  ///Set the color the Dial
  void SetColor(const int r, const int g, const int b);

  ///Set the greenness the Dial
  void SetGreen(const int g);

  ///Set the position of the Dial
  void SetPosition(const double position);

  ///Set the redness the Dial
  void SetRed(const int r);

  ///The signal emitted when the Dial its color is changed
  mutable boost::signals2::signal<void ()> m_signal_color_changed;

  ///The signal emitted when the Dial position is changed
  mutable boost::signals2::signal<void ()> m_signal_position_changed;

  private:
  //Dial can only be deleted by Boost smart pointers
  virtual ~Dial() {}
  friend void boost::checked_delete<>(Dial*);

  unsigned char m_red;
  unsigned char m_green;
  unsigned char m_blue;

  double m_position;

  friend std::ostream& operator<<(std::ostream& os, const Dial& dial);

  public:
  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);

  //From www.richelbilderbeek.nl/CppGetDistance.htm
  static double GetDistance(const double dX, const double dY);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

std::ostream& operator<<(std::ostream& os, const Dial& dial);

} //~namespace ribi

#endif // DIAL_H
