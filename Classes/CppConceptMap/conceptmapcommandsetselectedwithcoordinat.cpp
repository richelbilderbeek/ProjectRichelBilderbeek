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
#include "conceptmapcommandsetselectedwithcoordinat.h"

#include <cassert>


#include "conceptmap.h"
#include "conceptmapnode.h"

bool ribi::cmap::CommandSetSelectedWithCoordinat::CanDoCommandSpecific(const ConceptMap * const widget) const noexcept
{
  assert(widget);
  return
    widget->FindNodeAt(m_x,m_y).get();
}

void ribi::cmap::CommandSetSelectedWithCoordinat::DoCommandSpecific(ConceptMap * const concept_map) noexcept
{
  assert(CanDoCommandSpecific(concept_map));
  assert(concept_map);

  m_prev_selected = const_cast<const ConceptMap*>(concept_map)->GetSelected();
  m_widget = concept_map;

  const boost::shared_ptr<Node> node {
    concept_map->FindNodeAt(m_x,m_y)
  };

  concept_map->SetSelected( Nodes( { node } ) );

  assert(m_widget);
  assert(concept_map);
}

void ribi::cmap::CommandSetSelectedWithCoordinat::UndoSpecific() noexcept
{
  assert(m_widget);

  //Give back previous selection
  m_widget->SetSelected(m_prev_selected);

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
}
