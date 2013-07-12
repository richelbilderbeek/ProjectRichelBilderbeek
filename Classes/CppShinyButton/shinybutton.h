
/*
ShinyButton, toggle button class
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

//From http://www.richelbilderbeek.nl/CppShinyButton.htm

#ifndef SHINYBUTTON_H
#define SHINYBUTTON_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

///ShinyButton is a class for a toggle button
struct ShinyButton
{
  explicit ShinyButton(
    const double color,
    const double gradient,
    const std::string& text = "");

  ///Get the main color (the color in the middle) of the ShinyButton
  double GetColor() const { return m_color; }

  ///Get the change of gradient on the ShinyButton.
  ///The difference in color between the left and right of the ShinyButton
  double GetGradient() const { return m_gradient; }

  const std::string& GetText() const { return m_text; }

  ///Set the ShinyButton its color
  void SetColor(
    const double color,
    const double gradient);

  ///Set the ShinyButton its text
  void SetText(const std::string& text);

  ///The signal that is emitted when ShinyButton changes color
  mutable boost::signals2::signal<void ()> m_signal_color_changed;

  ///The signal that is emitted when ShinyButton changes color
  mutable boost::signals2::signal<void ()> m_signal_text_changed;

  private:
  //ShinyButton can only be deleted by Boost smart pointers
  virtual ~ShinyButton() {}
  //ShinyButton can only be deleted by Boost smart pointers
  friend void boost::checked_delete<>(ShinyButton*);

  ///\brief
  ///The main color of the ShinyButton
  ///
  ///m_color denotes the fraction [0.0,1.0] on the rainbow:
  ///0.0 = red, 1.0 = magenta
  double m_color;

  ///\brief
  ///The change of gradient on the ShinyButton
  ///
  ///Gradient goes from [m_color-(0.5*m_gradient),m_color+(0.5*m_gradient)]
  ///0.0 = no gradient = a single color
  ///1.0 = show the entire rainbow with m_color in the middle
  double m_gradient;

  ///The text displayed by the ShinyButton
  std::string m_text;

  friend std::ostream& operator<<(std::ostream& os, const ShinyButton& button);

  public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

std::ostream& operator<<(std::ostream& os, const ShinyButton& button);

#endif // SHINYBUTTON_H

