//---------------------------------------------------------------------------
/*
TestTimedServerPusher, tool to test WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestTimedServerPusher.htm
//---------------------------------------------------------------------------
#ifndef WTTESTTIMEDSERVERPUSHERMENUDIALOG_H
#define WTTESTTIMEDSERVERPUSHERMENUDIALOG_H
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>

namespace ribi {
namespace ToolTestTimedServerPusher {
//---------------------------------------------------------------------------
struct WtMenuDialog : public Wt::WContainerWidget
{
  WtMenuDialog();
  private:
  void CheckResources();
  Wt::WWidget * CreateNewAboutDialog();
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};
//---------------------------------------------------------------------------
} //~namespace ToolTestTimedServerPusher

} //~namespace ribi

#endif // WTTESTTIMEDSERVERPUSHERMENUDIALOG_H
