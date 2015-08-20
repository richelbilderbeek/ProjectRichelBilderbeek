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
#include "conceptmapcommandcreatenewconceptmap.h"

/*

#include <cassert>



bool ribi::cmap::CommandCreateNewConceptMap::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return !widget->GetConceptMap();
}

void ribi::cmap::CommandCreateNewConceptMap::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);

  assert(widget);
  assert(!widget->GetConceptMap().get());

  m_widget = widget;

  const boost::shared_ptr<ConceptMap> new_map {
    ConceptMapFactory().Create("...")
  };
  assert(new_map);
  m_widget->SetConceptMap(new_map);

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(m_widget->GetConceptMap().get());
}

void ribi::cmap::CommandCreateNewConceptMap::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  boost::shared_ptr<ConceptMap> empty_map;
  m_widget->SetConceptMap(empty_map);

  m_widget->m_signal_concept_map_changed();

  m_widget = nullptr;

}

*/
