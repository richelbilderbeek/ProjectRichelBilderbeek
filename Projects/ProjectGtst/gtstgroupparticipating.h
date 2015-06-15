
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

#ifndef PROJECTGTSTGROUPPARTICIPATING_H
#define PROJECTGTSTGROUPPARTICIPATING_H

#include "gtstgroup.h"


namespace ribi {
namespace gtst {

///GroupParticipating is a Participant Group that is participating
struct GroupParticipating : public Group
{
  ///Constructor that assigns an ID
  GroupParticipating(Server * const server);

  ///Get the Group its ID
  int GetId() const { return m_id; }

  static void Reset();

  ///Represent the Group type as a std::string
  const std::string ToStr() const { return "Participating"; }

  private:
  virtual ~GroupParticipating() {}
  friend void boost::checked_delete<>(GroupParticipating*);

  ///The Group its unique ID
  const int m_id;

  ///m_group_last_index contains the index given to the last group
  static int m_group_last_id;

};

} //~namespace gtst
} //~namespace ribi

#endif // GROUPPARTICIPATING_H
