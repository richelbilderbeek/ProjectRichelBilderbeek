//---------------------------------------------------------------------------
/*
ToggleButtonWidget, widget for the ToggleButton class
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
//From http://www.richelbilderbeek.nl/CppToggleButtonWidget.htm
//---------------------------------------------------------------------------
#ifndef TOGGLEBUTTONWIDGET_H
#define TOGGLEBUTTONWIDGET_H

#include <boost/scoped_ptr.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {

struct ToggleButton;

struct ToggleButtonWidget : public Widget
{
  explicit ToggleButtonWidget(
    const bool pressed = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255
  );

  ///Obtain a read-and-write pointer to ToggleButton
  ToggleButton * GetToggleButton() { return m_button.get(); }

  ///Obtain a read-only pointer to ToggleButton
  const ToggleButton * GetToggleButton() const { return m_button.get(); }

  ///Respond to the user clicking on this class
  void Click(const int x, const int y);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  boost::scoped_ptr<ToggleButton> m_button;

  friend std::ostream& operator<<(std::ostream& os, const ToggleButtonWidget& button);
};

std::ostream& operator<<(std::ostream& os, const ToggleButtonWidget& button);

} //~namespace ribi

#endif // TOGGLEBUTTONWIDGET_H
