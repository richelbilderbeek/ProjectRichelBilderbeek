//---------------------------------------------------------------------------
/*
WtTimedServerPusherClient, client of WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/CppWtTimedServerPusherClient.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>

#include <Wt/WApplication>

#include "wttimedserverpusher.h"
#include "wttimedserverpusherclient.h"
#pragma GCC diagnostic pop

ribi::WtTimedServerPusherClient::WtTimedServerPusherClient()
{
  Wt::WApplication::instance()->enableUpdates(true);
  ribi::WtTimedServerPusher::GetInstance()->Connect(
    this,boost::bind(&ribi::WtTimedServerPusherClient::OnServer,this));

  //Never call virtual functions during construction or destruction
  //Scott Meyers, Effective C++, item 9
  //OnServer();
}

ribi::WtTimedServerPusherClient::~WtTimedServerPusherClient()
{
  Wt::WApplication::instance()->enableUpdates(false);
  ribi::WtTimedServerPusher::GetInstance()->Disconnect(this);
}

std::string ribi::WtTimedServerPusherClient::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::WtTimedServerPusherClient::GetVersionHistory()
{
  return {
    "2011-08-05: version 1.0: initial version"
  };
}

void ribi::WtTimedServerPusherClient::OnServer()
{
  OnTimedServerPush();
  Wt::WApplication::instance()->triggerUpdate();
}

