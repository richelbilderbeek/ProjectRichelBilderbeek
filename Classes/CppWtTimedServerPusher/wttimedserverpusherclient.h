//---------------------------------------------------------------------------
/*
WtTimedServerPusherClient, client of WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/CppWtTimedServerPusherClient.htm
//---------------------------------------------------------------------------
#ifndef WTTIMEDSERVERPUSHERCLIENT_H
#define WTTIMEDSERVERPUSHERCLIENT_H

#include <string>
#include <vector>

namespace ribi {

///WtTimedServerPusherClient is a client responding to WtTimedServerPusher
///and to be used as a base class
struct WtTimedServerPusherClient
{
  virtual ~WtTimedServerPusherClient();

  ///Get the version of this class
  static const std::string GetVersion();

  ///Get the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///UpdatePage is called when the WtTimedServerPusher triggers an update by timer
  virtual void OnTimedServerPush() = 0;

  protected:
  ///WtTimedServerPusherClient constructor is protected
  ///because it is to be used as a base class
  WtTimedServerPusherClient();

  private:
  ///Respond to the server
  void OnServer();
};

} //~namespace ribi

#endif // WTTIMEDSERVERPUSHERCLIENT_H
