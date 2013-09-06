//---------------------------------------------------------------------------
/*
ToggleButton, toggle button class
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
//From http://www.richelbilderbeek.nl/CppToggleButton.htm
//---------------------------------------------------------------------------
#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///ToggleButton is a class for a toggle button
struct ToggleButton
{
  explicit ToggleButton(
    const bool pressed = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Get the blueness of the ToggleButton's surface
  unsigned char GetBlue() const { return m_blue; }

  ///Get the greenness of the ToggleButton's surface
  unsigned char GetGreen() const { return m_green; }

  ///Get the redness of the ToggleButton's surface
  unsigned char GetRed() const { return m_red; }

  ///Returns if the ToggleButton is pressed
  bool IsPressed() const { return m_pressed; }

  ///Press the ToggleButton
  void Press();

  ///Release/'unpress' the ToggleButton
  void Release();

  ///Set the ToggleButton its color
  void SetColor(
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue);

  ///Toggle the ToggleButton
  void Toggle();

  ///The signal that is emitted when ToggleButton changes color
  mutable boost::signals2::signal<void ()> m_signal_color_changed;


  ///The signal that is emitted when ToggleButton changes state
  mutable boost::signals2::signal<void ()> m_signal_toggled;

  private:
  //ToggleButton can only be deleted by Boost smart pointers
  virtual ~ToggleButton() {}
  //ToggleButton can only be deleted by Boost smart pointers
  friend void boost::checked_delete<>(ToggleButton*);

  ///Is the toggle button pressed?
  bool m_pressed;

  ///The redness of the ToggleButton's surface
  unsigned char m_red;

  ///The greenness of the ToggleButton's surface
  unsigned char m_green;

  ///The blueness of the ToggleButton's surface
  unsigned char m_blue;

  friend std::ostream& operator<<(std::ostream& os, const ToggleButton& button);

  public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

std::ostream& operator<<(std::ostream& os, const ToggleButton& button);

} //~namespace ribi

#endif // TOGGLEBUTTON_H

