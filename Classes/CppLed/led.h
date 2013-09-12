//---------------------------------------------------------------------------
/*
Led, LED class
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
//From http://www.richelbilderbeek.nl/CppLed.htm
//---------------------------------------------------------------------------
#ifndef LED_H
#define LED_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Led manages an LED lamp
struct Led : public boost::noncopyable
{
  explicit Led(
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green =   0,
    const unsigned char blue  =   0);

  mutable boost::signals2::signal<void ()> m_signal_color_changed;
  mutable boost::signals2::signal<void ()> m_signal_intensity_changed;

  ///Set the Led its color
  void SetColor(
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue);

  ///Get the Led its blueness
  unsigned char GetBlue()  const { return m_blue;  }

  ///Get the Led its greenness
  unsigned char GetGreen() const { return m_green; }

  ///Get the Led its intensity, from 0.0 to 1.0
  double GetIntensity() const { return m_intensity; }

  ///Get the Led its redness
  unsigned char GetRed()   const { return m_red;   }

  ///Set the Led its blueness
  void SetBlue(const unsigned char blue);

  ///Set the Led its greenness
  void SetGreen(const unsigned char green);

  ///Set the Led its intensity, from 0.0 to 1.0
  void SetIntensity(const double intensity);

  ///Set the Led its redness
  void SetRed(const unsigned char red);

  private:
  ///Led can only be deleted by Boost smart pointers
  virtual ~Led() {}
  ///Led can only be deleted by Boost smart pointers
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(Led*);

  ///m_intensity has range [0.0,1.0]
  double m_intensity;

  ///The Led its redness
  unsigned char m_red;

  ///The Led its greenness
  unsigned char m_green;

  ///The Led its blueness
  unsigned char m_blue;

  friend std::ostream& operator<<(std::ostream& os, const Led& led);

  public:
  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();
};

std::ostream& operator<<(std::ostream& os, const Led& led);

} //~namespace ribi

#endif // LED_H
