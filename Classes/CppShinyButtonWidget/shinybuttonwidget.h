//---------------------------------------------------------------------------
/*
ShinyButtonWidget, widget for the ShinyButton class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppShinyButtonWidget.htm
//---------------------------------------------------------------------------
#ifndef SHINYBUTTONWIDGET_H
#define SHINYBUTTONWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {

struct ShinyButton;

struct ShinyButtonWidget : public Widget
{
  explicit ShinyButtonWidget(
    const double color,
    const double gradient,
    const std::string& text = "",
    const Rect rect = CreateRect(0,0,80,20)
  );
  ShinyButtonWidget(const ShinyButtonWidget&) = delete;
  ShinyButtonWidget& operator=(const ShinyButtonWidget&) = delete;
  ~ShinyButtonWidget() noexcept {}

        ShinyButton * GetShinyButton()       noexcept { return m_button.get(); }
  const ShinyButton * GetShinyButton() const noexcept { return m_button.get(); }

  void Click() noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///The signal emitted when the ShinyButtonWidget is clicked
  mutable boost::signals2::signal<void (const ShinyButtonWidget* const)> m_signal_clicked;

  private:

  ///The ShinyButton
  boost::scoped_ptr<ShinyButton> m_button;

  ///Allow std::cout access to ShinyButtonWidget
  friend std::ostream& operator<<(std::ostream& os, const ShinyButtonWidget& button) noexcept;
};

std::ostream& operator<<(std::ostream& os, const ShinyButtonWidget& button) noexcept;

} //~namespace ribi

#endif // SHINYBUTTONWIDGET_H
