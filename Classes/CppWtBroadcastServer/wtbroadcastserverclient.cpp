//---------------------------------------------------------------------------
/*
WtBroadcastServerClient, client of WtBroadcastServer
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
//From http://www.richelbilderbeek.nl/CppWtBroadcastServerClient.htm
//---------------------------------------------------------------------------
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
//---------------------------------------------------------------------------
#include "wtbroadcastserver.h"
#include "wtbroadcastserverclient.h"
//---------------------------------------------------------------------------
WtBroadcastServerClient::WtBroadcastServerClient()
{
  Wt::WApplication::instance()->enableUpdates(true);
  WtBroadcastServer::GetInstance()->Connect(
    this,boost::bind(&WtBroadcastServerClient::OnServer,this));

  //Never call virtual functions during construction or destruction
  //Scott Meyers, Effective C++, item 9
  //OnServer();
}
//---------------------------------------------------------------------------
WtBroadcastServerClient::~WtBroadcastServerClient()
{
  Wt::WApplication::instance()->enableUpdates(false);
  WtBroadcastServer::GetInstance()->Disconnect(this);
}
//---------------------------------------------------------------------------
const std::string WtBroadcastServerClient::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtBroadcastServerClient::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-27: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtBroadcastServerClient::OnServer()
{
  UpdatePage();
  Wt::WApplication::instance()->triggerUpdate();
}
//---------------------------------------------------------------------------
