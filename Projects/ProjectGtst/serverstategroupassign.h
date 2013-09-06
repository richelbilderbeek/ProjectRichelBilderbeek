//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#ifndef SERVERSTATEGROUPASSIGN_H
#define SERVERSTATEGROUPASSIGN_H
//---------------------------------------------------------------------------
#include <map>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "serverstate.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///The Server in the state when each Participant is assigned his/her group
struct ServerStateGroupAssign : public ServerState, StateGroupAssign
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateGroupAssign(Server * const server, const int period, const int cycle);

  ///Request the server to assign the Participant to a Group
  void AssignGroup(const boost::shared_ptr<const Participant>& participant) const;

  ///Ask the server if the Participant can be asssigned to a Group
  bool CanAssignGroup(const boost::shared_ptr<const Participant>& participant) const;

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///Create this ServerState its specific Parameters
  //void SetParameters(const boost::shared_ptr<const ParametersGroupAssign>&);

  ///Start or restart the state, calculate the joiners
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateGroupAssign::ToStr(); }

  private:
  ///Only allow a Boost smart pointer to delete ServerStateGroupAssign
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ServerStateGroupAssign() {}
  ///Only allow a Boost smart pointer to delete ServerStateGroupAssign
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ServerStateGroupAssign*);

  friend std::ostream& operator<<(std::ostream& os,const ServerStateGroupAssign& s);

};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ServerStateGroupAssign& s);

} //~namespace gtst
} //~namespace ribi

#endif // SERVERSTATEGROUPASSIGN_H
