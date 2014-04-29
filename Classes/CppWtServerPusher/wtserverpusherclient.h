//---------------------------------------------------------------------------
/*
WtServerPusherClient, client of WtServerPusher
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
//From http://www.richelbilderbeek.nl/CppWtServerPusher.htm
//---------------------------------------------------------------------------
#ifndef WTSERVERPUSHERCLIENT_H
#define WTSERVERPUSHERCLIENT_H

#include <string>
#include <vector>

namespace ribi {

///WtServerPusherClient is a client responding to WtServerPusher
///and to be used as a base class
struct WtServerPusherClient
{
  virtual ~WtServerPusherClient();

  ///Get the version of this class
  static std::string GetVersion();

  ///Get the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///OnServerPush is called when the WtServerPusher is posted to
  virtual void OnServerPush() = 0;

  protected:
  ///WtServerPusherClient constructor is protected
  ///because it is to be used as a base class
  WtServerPusherClient();

  private:
  ///Respond to the server
  void OnServer();
};

} //~namespace ribi

#endif // WTSERVERPUSHERCLIENT_H
