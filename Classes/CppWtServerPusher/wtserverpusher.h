//---------------------------------------------------------------------------
/*
WtServerPusher, server to broadcast to all its WtServerPusherClients
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
//From http://www.richelbilderbeek.nl/CppWtServerPusher.htm
//---------------------------------------------------------------------------
#ifndef WTSERVERPUSHER_H
#define WTSERVERPUSHER_H

#include <mutex>
#include <thread>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct WtServerPusherClient;


///A Server that broadcasts its messages
struct WtServerPusher
{
  WtServerPusher(const WtServerPusher&) = delete;
  WtServerPusher& operator=(const WtServerPusher&) = delete;

  ///Let a WtServerPusherClient have its supplied function called by WtServerPusher::Run
  void Connect(WtServerPusherClient * const client, const boost::function<void()>& function);

  ///Stop a WtServerPusherClient have its supplied function called by TimePollServer::Run
  void Disconnect(const WtServerPusherClient* const client);

  ///Obtain the only instace to WtServerPusher
  static WtServerPusher * GetInstance();

  ///Get the version of this class
  static std::string GetVersion();

  ///Get the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///Post calls all WtServerPusherClients' supplied functions
  void Post();

private:
  //Connection is a non-copyable POD
  struct Connection
  {
    Connection(
      const std::string& session_id,
      WtServerPusherClient * client,
      const boost::function<void()>& function)
      : m_session_id(session_id),m_client(client),m_function(function)
    {

    }
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    const std::string m_session_id;
    WtServerPusherClient * const m_client;
    const boost::function<void()> m_function;
  };

  ///WtServerPusher constructor, which is private, because WtServerPusher follows
  ///the Singleton design pattern
  WtServerPusher();

  ///WtServerPusher destructor
  ~WtServerPusher();

  ///Only let a smart pointer (that is, m_instance) delete WtServerPusher
  friend void boost::checked_delete<>(WtServerPusher*);

  ///All connections to the WtServerPusherClients
  std::vector<boost::shared_ptr<Connection> > m_connections;

  ///The WtServerPusher its only instance
  static boost::scoped_ptr<WtServerPusher> m_instance;

  ///A mutex
  mutable std::mutex m_mutex;
};

} //~namespace ribi

#endif // WTSERVERPUSHER_H
