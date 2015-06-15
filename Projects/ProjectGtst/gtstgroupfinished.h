
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

#ifndef PROJECTGTSTGROUPFINISHED_H
#define PROJECTGTSTGROUPFINISHED_H

#include "gtststate.h"
#include "gtstgroup.h"


namespace ribi {
namespace gtst {

///GroupFinished is a Participant Group that is finished
struct GroupFinished : public Group, StateFinished
{
  GroupFinished(Server * const server);

  ///Add a Participant to this Group and set its State to Finished
  void AddFinishedParticipant(boost::shared_ptr<Participant> participant);

  ///GroupFinished its ID is the highest maximum int
  int GetId() const;

  ///Represent the Group type as a std::string
  const std::string ToStr() const { return this->StateFinished::ToStr(); }

  private:
  virtual ~GroupFinished() {}
  friend void boost::checked_delete<>(GroupFinished*);
};

} //~namespace gtst
} //~namespace ribi

#endif // GROUPFINISHED_H
