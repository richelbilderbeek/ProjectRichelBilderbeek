//---------------------------------------------------------------------------
/*
WtServerPusherClient, client of WtServerPusher
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
//From http://www.richelbilderbeek.nl/CppWtServerPusherClient.htm
//---------------------------------------------------------------------------
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
//---------------------------------------------------------------------------
#include "wtserverpusher.h"
#include "wtserverpusherclient.h"
//---------------------------------------------------------------------------
WtServerPusherClient::WtServerPusherClient()
{
  Wt::WApplication::instance()->enableUpdates(true);
  WtServerPusher::GetInstance()->Connect(
    this,boost::bind(&WtServerPusherClient::OnServer,this));

  //Never call virtual functions during construction or destruction
  //Scott Meyers, Effective C++, item 9
  //OnServer();
}
//---------------------------------------------------------------------------
WtServerPusherClient::~WtServerPusherClient()
{
  Wt::WApplication::instance()->enableUpdates(false);
  WtServerPusher::GetInstance()->Disconnect(this);
}
//---------------------------------------------------------------------------
const std::string WtServerPusherClient::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtServerPusherClient::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-27: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtServerPusherClient::OnServer()
{
  OnServerPush();
  Wt::WApplication::instance()->triggerUpdate();
}
//---------------------------------------------------------------------------
