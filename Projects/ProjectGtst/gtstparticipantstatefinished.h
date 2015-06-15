
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

#ifndef PROJECTGTSTPARTICIPANTSTATEFINISHED_H
#define PROJECTGTSTPARTICIPANTSTATEFINISHED_H
#include <boost/checked_delete.hpp>

#include "gtststate.h"
#include "gtstparticipantstate.h"


namespace ribi {
namespace gtst {

///The Participant is in the StateFinished ParticipantState
struct ParticipantStateFinished
  : public ParticipantState, StateFinished
{
  ///Contruct every ParticipantState from a pointer to its Participant
  ParticipantStateFinished(Participant * const participant,Server * const server);
  ///Represent the ParticipantState as a std::string for an Administrator
  const std::string ToAdminStr() const;
  ///Represent the State at a std::string
  const std::string ToStr() const { return this->StateFinished::ToStr(); }
  protected:
  ///Only let a smart pointer delete this ParticipantState
  virtual ~ParticipantStateFinished() {}
  ///Only let a smart pointer delete this ParticipantState
  friend void boost::checked_delete<>(ParticipantStateFinished*);
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTSTATEFINISHED_H
