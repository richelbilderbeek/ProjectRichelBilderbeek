//---------------------------------------------------------------------------
/*
Led, LED class
Copyright (C) 2011-2014 Richel Bilderbeek

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
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Led manages an LED lamp
struct Led
{
  explicit Led(
    const double intensity    = 0.0,
    const int red   = 255,
    const int green =   0,
    const int blue  =   0);
  Led(const Led&) = delete;
  Led& operator=(const Led&) = delete;

  mutable boost::signals2::signal<void (Led*)> m_signal_color_changed;
  mutable boost::signals2::signal<void (Led*)> m_signal_intensity_changed;

  ///Set the Led its color
  void SetColor(
    const int red,
    const int green,
    const int blue
  ) noexcept;

  ///Get the Led its blueness
  int GetBlue()  const noexcept { return m_blue;  }

  ///Get the Led its greenness
  int GetGreen() const noexcept { return m_green; }

  ///Get the Led its intensity, from 0.0 to 1.0
  double GetIntensity() const noexcept { return m_intensity; }

  ///Get the Led its redness
  int GetRed() const noexcept { return m_red;   }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the Led its blueness, range [0.0,255]
  void SetBlue(const int blue) noexcept;

  ///Set the Led its greenness, range [0.0,255]
  void SetGreen(const int green) noexcept;

  ///Set the Led its intensity, from 0.0 to 1.0
  void SetIntensity(const double intensity) noexcept;

  ///Set the Led its redness, range [0.0,255]
  void SetRed(const int red) noexcept;

  std::string ToStr() const noexcept;
  std::string ToXml() const noexcept;

  private:
  virtual ~Led() noexcept {}
  friend void boost::checked_delete<>(Led*);

  ///The Led its blueness, range [0.0,255]
  int m_blue;

  ///The Led its greenness, range [0.0,255]
  int m_green;

  ///m_intensity has range [0.0,1.0]
  double m_intensity;

  ///The Led its redness, range [0.0,255]
  int m_red;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Led& led) noexcept;

};

std::ostream& operator<<(std::ostream& os, const Led& led) noexcept;
bool operator==(const Led& lhs, const Led& rhs) noexcept;

} //~namespace ribi

#endif // LED_H
