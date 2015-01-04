//---------------------------------------------------------------------------
/*
MysteryMachineWidget, GUI independent widget for MysteryMachine
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
//From http://www.richelbilderbeek.nl/CppMysteryMachineWidget.htm
//---------------------------------------------------------------------------
#ifndef MYSTERYMACHINEWIDGET_H
#define MYSTERYMACHINEWIDGET_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/signals2.hpp>
#include <boost/tuple/tuple.hpp>

#include "widget.h"
#include "mysterymachinekey.h"
#pragma GCC diagnostic pop

namespace ribi {

struct MysteryMachine;
struct DialWidget;
struct TextCanvas;
struct ToggleButtonWidget;
struct LedWidget;

///MysteryMachineWidget handles the GUI independent
///user interface of the display of a MysteryMachine
struct MysteryMachineWidget : public Widget
{
  explicit MysteryMachineWidget(const Rect& geometry = CreateRect(0,0,200,400)) noexcept;

  ///Respond to the user clicking on the MysteryMachineWidget
  void Click(const int x, const int y) noexcept;

  const boost::shared_ptr<const MysteryMachine> GetMachine() const noexcept { return m_machine; }
  const boost::shared_ptr<      MysteryMachine> GetMachine()       noexcept { return m_machine; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  void PressKey(const MysteryMachineKey key) noexcept;

  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  boost::signals2::signal<void()> m_signal_changed;

  private:
  virtual ~MysteryMachineWidget() noexcept {}
  friend void boost::checked_delete<>(MysteryMachineWidget*);

  boost::shared_ptr<MysteryMachine> m_machine;

  static Rect CreateRect(
    const double left,
    const double top,
    const double width,
    const double height
  ) noexcept;

  ///Respond to a change in geometry
  void OnResize() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const MysteryMachineWidget& widget) noexcept;
};

std::ostream& operator<<(std::ostream& os, const MysteryMachineWidget& widget) noexcept;

} //~namespace ribi

#endif // MYSTERYMACHINEWIDGET_H
