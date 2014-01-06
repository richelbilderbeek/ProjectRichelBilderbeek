//---------------------------------------------------------------------------
/*
MysteryMachineWidget, GUI independent widget for MysteryMachine
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
#include "rectangle.h"
#pragma GCC diagnostic pop

namespace ribi {

struct MysteryMachine;
struct DialWidget;
struct ToggleButtonWidget;
struct LedWidget;

///MysteryMachineWidget handles the GUI independent
///user interface of the display of a MysteryMachine
struct MysteryMachineWidget : public Widget
{
  explicit MysteryMachineWidget(const Rect& geometry = Rect(0,0,200,400)) noexcept;

  ///Respond to the user clicking on the MysteryMachineWidget
  void Click(const int x, const int y) noexcept;

  const MysteryMachine * GetMachine() const { return m_machine.get(); }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  private:
  virtual ~MysteryMachineWidget() noexcept {}
  friend void boost::checked_delete<>(MysteryMachineWidget*);

  boost::scoped_ptr<MysteryMachine> m_machine;

  ///Respond to a change in geometry
  void OnResize() noexcept;

  friend std::ostream& operator<<(std::ostream& os, const MysteryMachineWidget& widget) noexcept;
};

std::ostream& operator<<(std::ostream& os, const MysteryMachineWidget& widget) noexcept;

} //~namespace ribi

#endif // MYSTERYMACHINEWIDGET_H
