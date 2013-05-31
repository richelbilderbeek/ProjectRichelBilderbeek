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
#ifndef WTCONNECTTHREERESOURCES_H
#define WTCONNECTTHREERESOURCES_H
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "connectthreeresources.h"
//---------------------------------------------------------------------------
namespace Wt
{
  struct WResource;
}
//---------------------------------------------------------------------------
///WtConnectThreeResources is a Singleton that manages
///all Wt resources. Its base class, ConnectThreeResources,
///ensures the files needed are present upon construction.
struct WtConnectThreeResources
  : public ConnectThreeResources
{
  static WtConnectThreeResources * GetInstance();

  #ifdef DO_REALLY_REALLY_USE_WT_RESOURCES
  const std::vector<boost::shared_ptr<Wt::WResource> > & GetComputers() const { return m_computers; }
  const boost::shared_ptr<Wt::WResource>& GetComputerGrey() const { return m_computer_grey; }
  const boost::shared_ptr<Wt::WResource>& GetEmpty() const { return m_empty; }
  const std::vector<boost::shared_ptr<Wt::WResource> > & GetInstructionsGood() const { return m_instructions_good; }
  const boost::shared_ptr<Wt::WResource>& GetInstructionsWrong() const { return m_instructions_wrong; }
  const std::vector<boost::shared_ptr<Wt::WResource> > & GetPlayers() const { return m_players; }
  const std::vector<boost::shared_ptr<Wt::WResource> > & GetPlayersGrey() const { return m_players_grey; }
  #endif

  private:
  WtConnectThreeResources();

  #ifdef DO_REALLY_REALLY_USE_WT_RESOURCES
  const boost::shared_ptr<Wt::WResource> m_background;
  const std::vector<boost::shared_ptr<Wt::WResource> > m_computers;
  const boost::shared_ptr<Wt::WResource> m_computer_grey;
  const boost::shared_ptr<Wt::WResource> m_empty;
  const std::vector<boost::shared_ptr<Wt::WResource> > m_instructions_good;
  const boost::shared_ptr<Wt::WResource> m_instructions_wrong;
  const std::vector<boost::shared_ptr<Wt::WResource> > m_players;
  const std::vector<boost::shared_ptr<Wt::WResource> > m_players_grey;
  #endif
  static WtConnectThreeResources * m_instance;
};

#endif // WTCONNECTTHREERESOURCES_H
