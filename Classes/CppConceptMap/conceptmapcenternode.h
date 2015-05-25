//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#ifndef CONCEPTMAPCENTERNODE_H
#define CONCEPTMAPCENTERNODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapnode.h"
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///The focal question of a ConceptMap
///- Every ConceptMap usually has one CenterNode
///- Every sub concept-map has none or one CenterNode
///  (a sub concet-map has a focal node instead)
struct CenterNode : public Node
{
  ///Block destructor, except for the friend boost::checked_delete
  ~CenterNode() noexcept {}
  friend void boost::checked_delete<>(CenterNode* x);

  ///Block construction, except for NodeFactory
  friend struct CenterNodeFactory;
  CenterNode() = delete;

  //lock to enforce use of CenterNodeFactory
  explicit CenterNode(
    const boost::shared_ptr<Concept>& concept,
    const double x,
    const double y,
    const CenterNodeFactory& lock
  );

  std::string ToXml() const noexcept;
};

///Returns true if Node is of derived class type CenterNode
///Returns true if Node is Node
bool IsCenterNode(const boost::shared_ptr<const Node> node) noexcept;

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPCENTERNODE_H
