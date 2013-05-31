//---------------------------------------------------------------------------
/*
WtTimedServerPusherClient, client of WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/CppWtTimedServerPusherClient.htm
//---------------------------------------------------------------------------
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
//---------------------------------------------------------------------------
#include "wttimedserverpusher.h"
#include "wttimedserverpusherclient.h"
//---------------------------------------------------------------------------
WtTimedServerPusherClient::WtTimedServerPusherClient()
{
  Wt::WApplication::instance()->enableUpdates(true);
  WtTimedServerPusher::GetInstance()->Connect(
    this,boost::bind(&WtTimedServerPusherClient::OnServer,this));

  //Never call virtual functions during construction or destruction
  //Scott Meyers, Effective C++, item 9
  //OnServer();
}
//---------------------------------------------------------------------------
WtTimedServerPusherClient::~WtTimedServerPusherClient()
{
  Wt::WApplication::instance()->enableUpdates(false);
  WtTimedServerPusher::GetInstance()->Disconnect(this);
}
//---------------------------------------------------------------------------
const std::string WtTimedServerPusherClient::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtTimedServerPusherClient::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-08-05: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtTimedServerPusherClient::OnServer()
{
  OnTimedServerPush();
  Wt::WApplication::instance()->triggerUpdate();
}
//---------------------------------------------------------------------------
