
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

#ifndef PROJECTGTSTGROUPLOGGEDIN_H
#define PROJECTGTSTGROUPLOGGEDIN_H

#include "gtstgroup.h"


namespace ribi {
namespace gtst {

///GroupLoggedIn is a Participant Group that is logged in
struct GroupLoggedIn : public Group
{
  GroupLoggedIn(Server * const server);

  ///GroupLoggedIn its ID is the highest maximum int minus one
  int GetId() const;

  ///Represent the Group type as a std::string
  const std::string ToStr() const { return "Logged in"; }

  ///Check if a Participant can log in with his/her IP address
  ///bool CanLoginParticipant(const std::string& ip_address) const;

  private:
  virtual ~GroupLoggedIn() {}
  friend void boost::checked_delete<>(GroupLoggedIn*);
};

} //~namespace gtst
} //~namespace ribi

#endif // GROUPLOGGEDIN_H
