
/*
GTST, Game Theory Server
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

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTSERVER_H
#define PROJECTGTSTSERVER_H

#include <iosfwd>
#include <mutex>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "gtstforward_declarations.h"
#include "wttimedserverpusherclient.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///The center of communication.
///
///Server is a thread-safe Non-copyable Singleton
///this is a client of WtTimedServerPusher
struct Server : public WtTimedServerPusherClient
{
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;

  ///Deletes all Participant instances
  void DeleteParticipants();

  ///Let an Administrator log in
  boost::weak_ptr<Administrator> LoginAdministrator();

  ///Let a Participant with a certain IP address log in for the first or later time
  const boost::shared_ptr<const Participant> LetLogin(const boost::shared_ptr<const SafeIpAddress>& ip_address);

  ///Obtain the Administrator collection
  const boost::weak_ptr<const Administrators> GetAdministrators() const { return m_administrators; }

  ///Obtain the Administrator collection
  boost::weak_ptr<Administrators> GetAdministrators() { return m_administrators; }

  ///Obtain a read-only pointer to Groups
  const Groups * GetGroups() const;

  ///Obtain a read-and-write pointer to Groups
  Groups * GetGroups();

  ///Obtain the Log File, read-only
  const LogFile * GetLog() const;

  ///Obtain the Log File
  LogFile * GetLog();

  ///Obtain the ServerStates, read-only
  const ServerStates * GetStates() const;

  ///Obtain the ServerStates
  ServerStates * GetStates();

  ///Obtain the Parameters
  const Parameters * GetParameters() const;

  ///Sets the Parameters
  ///
  ///\note
  ///Effects all member variables, except the Administrators
  void SetParameters(boost::shared_ptr<Parameters> parameters);

  ///Set the current ServerState to its new state
  //void SetState(const State * const new_state);

  //Nobody ever logs out: he/she just refreshes or has a browser crash
  //When the browser is closed, the server is notified. This is not
  //the case when a browser is refreshed (by pressing F5, for example)
  void NotifyLogout(const boost::shared_ptr<const Participant>& participant);

  ///Resets the server to its initial state
  void Reset();

  ///Test the Server
  void TestMe();

  private:
  ///Constructor is as private as Server is Singleton
  Server();

  ///Obtain the Server Singleton's only instance
  static Server * Get();

  ///The set of active Administrators
  boost::shared_ptr<Administrators> m_administrators;

  ///The Groups Facade
  boost::shared_ptr<Groups> m_groups;

  ///The only instance of the Server
  static boost::scoped_ptr<Server> m_instance;

  ///The LogFile
  boost::shared_ptr<LogFile> m_log;

  ///The parameters when not/yes loaded
  boost::shared_ptr<Parameters> m_parameters;

  ///Public mutex when reading/writing to Server,
  static std::recursive_mutex m_mutex;

  ///The ServerState instances
  boost::shared_ptr<ServerStates> m_states;

  ///Respond to the TimedServerPusher
  void OnTimedServerPush();

  ///Give friendship to ServerState for the FindParticipant method
  friend class ServerState;

  ///Give friendship to the only Server::Get caller
  friend class MenuDialog;
};

} //~namespace gtst
} //~namespace ribi

#endif // SERVER_H
