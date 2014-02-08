//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#ifndef WTCONNECTTHREEMENUDIALOG_H
#define WTCONNECTTHREEMENUDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>

#include "connectthreeresources.h"

namespace Wt
{
  struct WMenu;
  struct WWidget;
}

namespace ribi {

struct WtSelectPlayerWidget;
struct WtAboutDialog;
struct WtConnectThreeGameDialog;

struct WtConnectThreeMenuDialog : public Wt::WContainerWidget
{
  WtConnectThreeMenuDialog();
  WtConnectThreeMenuDialog(
    const boost::shared_ptr<const ConnectThreeResources> resources
  );
  WtConnectThreeMenuDialog(const WtConnectThreeMenuDialog&) = delete;
  WtConnectThreeMenuDialog& operator=(const WtConnectThreeMenuDialog&) = delete;

  private:
  WtConnectThreeGameDialog * m_game;
  Wt::WMenu * m_menu;
  WtSelectPlayerWidget * m_select;
  WtConnectThreeGameDialog * CreateNewGameDialog();
  Wt::WWidget * CreateNewWelcomeDialog() const;
  Wt::WWidget * CreateNewSelectPlayersDialog();
  static const boost::shared_ptr<const ConnectThreeResources> CreateResources();
  void OnMenuItemChanged();
  void OnSelectClicked();
  public:
  static WtAboutDialog * CreateNewAboutDialog();
  const boost::shared_ptr<const ConnectThreeResources> m_resources;
};

} //~namespace ribi

#endif // WTCONNECTTHREEMENUDIALOG_H
