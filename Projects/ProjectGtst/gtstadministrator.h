//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#ifndef PROJECTGTSTADMINISTRATOR_H
#define PROJECTGTSTADMINISTRATOR_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///Administrator is a user with all (administrator) rights.
///
///Administrator is an administrator. There are any number of Administrator
///instances possible during a single session.
struct Administrator
{
  ///Each Administrator has a unique ID
  explicit Administrator(const int id);
  Administrator(const Administrator&) = delete;
  Administrator& operator=(const Administrator&) = delete;

  ///Get the Administrator his/her ID
  int GetId() const;

  private:
  ~Administrator() {}
  friend void boost::checked_delete<>(Administrator*);

  ///Every administrator has a unique ID.
  ///This ID is uncorrelated with Participant::m_id
  const int m_id;
};

std::ostream& operator<<(std::ostream& os,const Administrator& administrator);


} //~namespace gtst
} //~namespace ribi

#endif // PROJECTGTSTADMINISTRATOR_H
