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
#include "conceptmapcommanddeleteedge.h"

#include <cassert>

#include "conceptmap.h"


ribi::cmap::CommandDeleteEdge::CommandDeleteEdge(
  const boost::shared_ptr<ConceptMap> conceptmap,
  const boost::shared_ptr<Edge> edge
)
  :
    m_conceptmap{conceptmap},
    m_edge{edge}
{
  assert(m_edge);

  if (!m_conceptmap->HasEdge(m_edge))
  {
    throw std::logic_error("CommandDeleteEdge cannot delete an Edge that is not present in the ConceptMap");
  }

  setText("delete edge");

}

void ribi::cmap::CommandDeleteEdge::redo()
{
  m_conceptmap->DeleteEdge(m_edge);
}

void ribi::cmap::CommandDeleteEdge::undo()
{
  m_conceptmap->AddEdge(m_edge);
}
