
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

#ifndef PROJECTGTSTSERVERSTATEVIEWRESULTSGROUP_H
#define PROJECTGTSTSERVERSTATEVIEWRESULTSGROUP_H

#include <map>

#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
//

#include "gtstserverstate.h"

namespace ribi {
namespace gtst {

///\brief
///The Server in the state when each Participant can view
///the results of his/her group.
struct ServerStateViewResultsGroup : public ServerState, StateViewResultsGroup
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateViewResultsGroup(
    Server * const server, const int period, const int cycle,
    const boost::shared_ptr<const ParametersViewResultsGroup>& parameters);

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///Create this ServerState its specific Parameters
  //void SetParameters(const boost::shared_ptr<const ParametersViewResultsGroup>& parameters);

  ///Get the Participant-dependent results
  //std::vector<std::string> GetResults(
  //  const Participant * const participant) const;

  ///Start or restart the state
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateViewResultsGroup::ToStr(); }

  private:
  ~ServerStateViewResultsGroup() {}
  friend void boost::checked_delete<>(ServerStateViewResultsGroup*);

  friend std::ostream& operator<<(std::ostream& os,const ServerStateViewResultsGroup& s);

  ///The ParametersViewResultsGroup
  const boost::shared_ptr<const ParametersViewResultsGroup> m_parameters;

};

std::ostream& operator<<(std::ostream& os,const ServerStateViewResultsGroup& s);

} //~namespace gtst
} //~namespace ribi

#endif // ServerSTATEVIEWRESULTSGROUP_H
