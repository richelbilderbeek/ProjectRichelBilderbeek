//---------------------------------------------------------------------------
/*
TestServerPusher, tool to test WtServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestServerPusher.htm
//---------------------------------------------------------------------------
#ifndef WTTESTSERVERPUSHERMAINDIALOG_H
#define WTTESTSERVERPUSHERMAINDIALOG_H
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
#include "wtserverpusherclient.h"
//---------------------------------------------------------------------------
namespace Wt
{
  struct WLineEdit;
}
//---------------------------------------------------------------------------
namespace ToolTestServerPusher {
//---------------------------------------------------------------------------
///TestServerPusher its main dialog
struct WtMainDialog : public Wt::WContainerWidget, WtServerPusherClient
{
  WtMainDialog();

  private:
  ///The user interface
  struct Ui
  {
    Ui() : m_edit(0) {}
    Wt::WLineEdit * m_edit;
  } ui;

  ///The user changes the text in the Wt::WLineEdit
  void OnEditChanged();

  ///The server updates the page
  void OnServerPush();
};
//---------------------------------------------------------------------------
} //~namespace ToolTestServerPusher
//---------------------------------------------------------------------------

#endif // WTTESTSERVERPUSHERMAINDIALOG_H
