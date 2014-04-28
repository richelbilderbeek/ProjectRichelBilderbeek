//---------------------------------------------------------------------------
/*
TestBroadcastServer, tool to test WtBroadcastServer
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
//From http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm
//---------------------------------------------------------------------------
#ifndef WTTESTBROADCASTSERVERMENUDIALOG_H
#define WTTESTBROADCASTSERVERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {
namespace ToolTestBroadcastServer {

struct WtMenuDialog : public Wt::WContainerWidget
{
  WtMenuDialog();
  private:
  void CheckResources();
  Wt::WWidget * CreateNewAboutDialog();
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};

} //~namespace ribi
} //~namespace ToolTestBroadcastServer

#endif // WTTESTBROADCASTSERVERMENUDIALOG_H
