
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

#ifndef PROJECTGTSTSERVERSTATECHOOSEACTION_H
#define PROJECTGTSTSERVERSTATECHOOSEACTION_H

#include "gtststate.h"
#include "gtstserverstate.h"


namespace ribi {
namespace gtst {

///\brief
///The Server is in the choose-action state
struct ServerStateChooseAction : public ServerState, StateChooseAction
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateChooseAction(
    Server * const server,
    const int period,
    const int cycle,
    const boost::shared_ptr<const ParametersChooseAction> parameters);

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///The Server is notified by ParticipantDialogChooseAction
  ///of the action taken by its Participant
  void NotifyChosenAction(
    const boost::shared_ptr<const Participant>& participant,
    const ChooseActionOption * const option);

  ///Create this ServerState its specific Parameters
  void SetParameters(const boost::shared_ptr<const ParametersChooseAction>& parameters);

  ///Start or restart the state, for example by resetting the timer
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateChooseAction::ToStr(); }

  private:
  ~ServerStateChooseAction() {}
  friend void boost::checked_delete<>(ServerStateChooseAction*);

  friend std::ostream& operator<<(std::ostream& os,const ServerStateChooseAction& s);

  ///Keeps track of Participants having voted
  std::map<boost::shared_ptr<const Participant>,bool> m_has_chosen_action;

  const boost::shared_ptr<const ParametersChooseAction> m_parameters;
};

std::ostream& operator<<(std::ostream& os,const ServerStateChooseAction& s);

} //~namespace gtst
} //~namespace ribi

#endif // ServerSTATECHOOSEACTION_H
