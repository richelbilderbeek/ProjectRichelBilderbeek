
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

#ifndef PROJECTGTSTGROUPASSIGNER_H
#define PROJECTGTSTGROUPASSIGNER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///GroupAssigner is the (abstract) base class to assign a group
///number to a Participant when the client logs in.
///
///GroupAssigner is a Strategy.
struct GroupAssigner
{
  GroupAssigner() {}

  //Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules,
  //guidelines, and best practices. ISBN: 0-32-111358-6. Item 50: 'Make base
  //class destructors public and virtual, or protected and nonvirtual'.
  virtual ~GroupAssigner() {}

  ///\brief Assign or unassign a Participant to a group.
  ///
  ///If Assign return -1, the Participant is removed from a group
  //virtual int Assign(const int id) const = 0;

  static boost::shared_ptr<GroupAssigner> CreateAssigner(const std::string& s);
};

///\brief
///A GroupAssigner that lets a Participant be assigned to always the same group
struct GroupAssignerPredetermined : public GroupAssigner
{
  ///GroupAssignerPredetermined needs the predetermined group index
  GroupAssignerPredetermined(const int group) : m_group(group) {}

  ///Get this GroupAssigner its group index, which is predetermined
  int GetGroup() const { return m_group; }

  ///\brief Assign or unassign a Participant to a group.
  ///
  ///If Assign return -1, the Participant is removed from a group
  //int Assign(const int /* id */) const { return m_group; }

  private:
  ~GroupAssignerPredetermined() {}
  friend void boost::checked_delete<>(GroupAssignerPredetermined*);

  const int m_group;
};

///\brief
///A GroupAssigner that lets a Participant be assigned to always the same group
struct GroupAssignerDeterminedByServer: public GroupAssigner
{
  GroupAssignerDeterminedByServer(/*const Server * const server*/);

  ///\brief Assign or unassign a Participant to a group.
  ///
  ///If Assign return -1, the Participant is removed from a group
  //int Assign(const int id) const;

  private:
  ~GroupAssignerDeterminedByServer() {}
  friend void boost::checked_delete<>(GroupAssignerDeterminedByServer*);

  ///Read-only pointer to server
  //const Server * const m_server;

  ///Read-only pointer to the Participant
  ///const Participant * m_participant;
};

} //~namespace gtst
} //~namespace ribi

#endif // GROUPASSIGNER_H
