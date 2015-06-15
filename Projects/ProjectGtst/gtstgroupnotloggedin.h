
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

#ifndef PROJECTGTSTGROUPNOTLOGGEDIN_H
#define PROJECTGTSTGROUPNOTLOGGEDIN_H

#include "gtstgroup.h"


namespace ribi {
namespace gtst {

///GroupNotLoggedIn is a Participant Group that is not logged in
struct GroupNotLoggedIn : public Group
{
  GroupNotLoggedIn(Server * const server);

  ///GroupNotLoggedIn its ID is the highest maximum int minus two
  int GetId() const;

  ///Represent the Group type as a std::string
  const std::string ToStr() const { return "Not logged in"; }

  ///Check if a Participant can log in with his/her IP address
  //bool CanLoginParticipant(const std::string& ip_address) const;

  private:
  virtual ~GroupNotLoggedIn() {}
  friend void boost::checked_delete<>(GroupNotLoggedIn*);
};

} //~namespace gtst
} //~namespace ribi

#endif // GROUPNOTLOGGEDIN_H
