
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

#ifndef PROJECTGTSTSERVERSTATES_H
#define PROJECTGTSTSERVERSTATES_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "gtstforward_declarations.h"


namespace ribi {
namespace gtst {

///ServerStates hold all Server states
struct ServerStates
{
  ///Server must be added as an argument to prevent recursive calls between
  ///ServerStates::ServerStates and Server::Server
  ServerStates(
    Server * const server,
    boost::shared_ptr<const Parameters> parameters,
    LogFile * const log);
  ServerStates(const ServerStates&) = delete;
  ServerStates& operator=(const ServerStates&) = delete;

  ///Get the current ServerState
  ServerState * GetCurrentState();

  ///Get the current ServerState, read-only
  const ServerState * GetCurrentState() const;

  int GetCycles(const int period) const;

  ///Let the Sequence go to the next state
  void GoToNextState();

  ///Set the Parameters
  //void SetParameters(boost::shared_ptr<const Parameters> parameters);

  private:
  ~ServerStates() {}
  friend void boost::checked_delete<>(ServerStates*);

  ///The current ServerState index
  int m_i;

  ///The LogFile
  LogFile * const m_log;

  ///The map that maps the period (= key) to the number of IPGG cycles
  std::map<int,int> m_n_cycles;

  ///The chronological collection of ServerState instances
  std::vector<boost::shared_ptr<ServerState> > m_v;

};

} //~namespace gtst
} //~namespace ribi

#endif // PROJECTGTSTSERVERSTATES_H
