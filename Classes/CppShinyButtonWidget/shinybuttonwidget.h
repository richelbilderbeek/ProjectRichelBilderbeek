
/*
ShinyButtonWidget, widget for the ShinyButton class
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

//From http://www.richelbilderbeek.nl/CppShinyButtonWidget.htm

#ifndef SHINYBUTTONWIDGET_H
#define SHINYBUTTONWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include "widget.h"

struct ShinyButton;

struct ShinyButtonWidget : public Widget
{
  explicit ShinyButtonWidget(
    const double color,
    const double gradient,
    const std::string& text = "",
    const Rect rect = Rect(80,20));

  ///Obtain a read-and-write pointer to ShinyButton
  ShinyButton * GetShinyButton() { return m_button.get(); }

  ///Obtain a read-only pointer to ShinyButton
  const ShinyButton * GetShinyButton() const { return m_button.get(); }

  ///Respond to the user clicking on this class
  void Click();

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///The signal emitted when the ShinyButtonWidget is clicked
  mutable boost::signals2::signal<void (const ShinyButtonWidget* const)> m_signal_clicked;

  private:

  ///The ShinyButton
  boost::scoped_ptr<ShinyButton> m_button;

  ///Allow std::cout access to ShinyButtonWidget
  friend std::ostream& operator<<(std::ostream& os, const ShinyButtonWidget& button);
};

std::ostream& operator<<(std::ostream& os, const ShinyButtonWidget& button);

#endif // SHINYBUTTONWIDGET_H
