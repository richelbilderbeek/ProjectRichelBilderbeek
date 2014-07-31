//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPCENTERNODE_H
#define QTCONCEPTMAPCENTERNODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtconceptmapnode.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///The center node
struct QtCenterNode : public QtNode
{
  ///Node cannot be const, as it contains a Concept the user might want to edit
  ///(that is, when a sub-concept map is created from a concept map and the
  ///focal node needs to be rated)
  ///concept_item is the display Strategy
  explicit QtCenterNode(const boost::shared_ptr<CenterNode> node);

  private:
  //static const boost::shared_ptr<QtItemDisplayStrategy> CreateConceptItem(const boost::shared_ptr<Node> node);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCENTERNODE_H
