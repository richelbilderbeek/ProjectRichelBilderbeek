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
#ifndef PROJECTGTSTADMINISTRATOR_H
#define PROJECTGTSTADMINISTRATOR_H
//---------------------------------------------------------------------------
#include <iosfwd>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
namespace ribi {
namespace gtst {

///\brief
///Administrator is a user with all (administrator) rights.
///
///Administrator is an administrator. There are any number of Administrator
///instances possible during a single session.
struct Administrator : public boost::noncopyable
{
  ///Each Administrator has a unique ID
  Administrator(const int id);

  ///Get the Administrator his/her ID
  int GetId() const;

  private:
  ///Only allow a Boost smart pointer to delete Administrator,
  ///To prevent the following trouble,
  ///cited from http://www.boost.org/libs/utility/checked_delete.html:
  ///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  ///class types to be deleted with a delete-expression.
  ///When the class has a non-trivial destructor, or a class-specific operator
  ///delete, the behavior is undefined. Some compilers issue a warning when an
  ///incomplete type is deleted, but unfortunately, not all do, and programmers
  ///sometimes ignore or disable warnings.
  ~Administrator() {}
  ///Only allow a Boost smart pointer to delete Administrator,
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(Administrator*);

  ///Every administrator has a unique ID.
  ///This ID is uncorrelated with Participant::m_id
  const int m_id;
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const Administrator& administrator);
//---------------------------------------------------------------------------

} //~namespace gtst
} //~namespace ribi

#endif // PROJECTGTSTADMINISTRATOR_H
