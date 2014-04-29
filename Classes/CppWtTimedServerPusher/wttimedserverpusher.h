//---------------------------------------------------------------------------
/*
WtTimedServerPusher, server to broadcast to all its WtTimedServerPusherClients
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
//From http://www.richelbilderbeek.nl/CppWtTimedServerPusher.htm
//---------------------------------------------------------------------------
#ifndef WTTIMEDSERVERPUSHER_H
#define WTTIMEDSERVERPUSHER_H

#include <mutex>
#include <thread>
#include <vector>

#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>


namespace ribi {

struct WtTimedServerPusherClient;

///A Server that broadcasts its messages
struct WtTimedServerPusher
{
  ///Let a WtTimedServerPusherClient have its supplied function called by WtTimedServerPusher::Run
  void Connect(WtTimedServerPusherClient * const client, const boost::function<void()>& function);

  ///Stop a WtTimedServerPusherClient have its supplied function called by TimePollServer::Run
  void Disconnect(const WtTimedServerPusherClient* const client);

  public:
  ///Obtain the only instace to WtTimedServerPusher
  static WtTimedServerPusher * GetInstance();

  ///Get the version of this class
  static const std::string GetVersion();

  ///Get the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///\brief
  ///Set the time (in milliseconds) WtTimedServerPusherClient::UpdatePage is to be called
  ///
  ///Use a time of zero to only let WtTimedServerPusherClient::UpdatePage be
  ///called upon Post
  void SetTime(const int time);

private:
  //Connection is a POD
  struct Connection
  {
    Connection(
      const std::string& session_id,
      WtTimedServerPusherClient * client,
      const boost::function<void()>& function)
      : m_session_id(session_id),m_client(client),m_function(function)
    {

    }
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    const std::string m_session_id;
    WtTimedServerPusherClient * const m_client;
    const boost::function<void()> m_function;
  };

  ///WtTimedServerPusher constructor, which is private, because WtTimedServerPusher follows
  ///the Singleton design pattern
  WtTimedServerPusher();

  ///WtTimedServerPusher destructor
  ~WtTimedServerPusher();

  ///Only let a smart pointer (that is, m_instance) delete WtTimedServerPusher
  friend void boost::checked_delete<>(WtTimedServerPusher*);

  ///All connections to the WtTimedServerPusherClients
  std::vector<boost::shared_ptr<Connection> > m_connections;

  ///The WtTimedServerPusher its only instance
  static boost::scoped_ptr<WtTimedServerPusher> m_instance;

  ///The data, can be anything
  boost::any m_data;

  ///A mutex
  mutable std::mutex m_mutex;

  ///If the Server is running
  bool m_running;

  ///The thread for WtTimedServerPusher::Run
  std::thread m_thread;

  ///The number of milliseconds before Run triggers Post
  int m_time;

  ///The method that is called every 100 msecs
  void Run();
};

} //~namespace ribi

#endif // WTTIMEDSERVERPUSHER_H
