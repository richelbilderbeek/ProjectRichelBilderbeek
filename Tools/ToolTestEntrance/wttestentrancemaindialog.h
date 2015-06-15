//---------------------------------------------------------------------------
/*
TestEntrance, tool to test WtEntrance
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
//From http://www.richelbilderbeek.nl/ToolTestEntrance.htm
//---------------------------------------------------------------------------
#ifndef WTTESTENTRANCEMAINDIALOG_H
#define WTTESTENTRANCEMAINDIALOG_H

#include <Wt/WContainerWidget>

namespace Wt
{
  struct WLineEdit;
}

namespace ribi {

struct IpAddress;

namespace ToolTestEntrance {

///TestEntrance its main dialog
struct WtMainDialog : public Wt::WContainerWidget
{
  WtMainDialog(boost::shared_ptr<const IpAddress> ip_address);

  private:

  ///Create the Welcome dialog
  Wt::WWidget * CreateNewWelcomeDialog();

  ///Respond to the user changing the name edit
  void OnEditChanged();

  ///Respond to a visitor changing his/her name
  void OnNewName();

  ///Respond to a new visitor
  void OnNewVisit();

  const boost::shared_ptr<const IpAddress> m_ip_address;

  struct Ui
  {
    Ui();
    Wt::WLineEdit * const m_edit;
    Wt::WContainerWidget * const m_view_names_dialog;
    Wt::WContainerWidget * const m_view_visits_dialog;
  } ui;
};

} //~namespace ToolTestEntrance

} //~namespace ribi

#endif // WTTESTENTRANCEMAINDIALOG_H
