//---------------------------------------------------------------------------
/*
Rasper, Raspberry Pi GPIO web application controller
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRasper.htm
//---------------------------------------------------------------------------
#ifndef WTRASPERMENUDIALOG_H
#define WTRASPERMENUDIALOG_H

#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>


namespace ribi {

struct IpAddress;

namespace ToolRasper {

struct WtMenuDialog : public Wt::WContainerWidget
{
  WtMenuDialog();
  private:
  Wt::WWidget * CreateNewAboutDialog();
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};

} //~namespace ToolRasper
} //~namespace ribi

#endif // WTRASPERMENUDIALOG_H
