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
#include <sstream>

#include "conceptmap.h"
#include "conceptmapnode.h"

ribi::cmap::CommandSetSelectedWithCoordinat::CommandSetSelectedWithCoordinat(
  const boost::shared_ptr<ConceptMap> conceptmap,
  const int x, const int y)
  : m_prev_selected{},
    m_conceptmap{conceptmap},
    m_node{conceptmap->FindNodeAt(m_x,m_y)},
    m_x{x},
    m_y{y}
{
  setText("set focus with coordinat");
  if (!m_conceptmap->FindNodeAt(m_x,m_y))
  {
    std::stringstream msg;
    msg
      << "Cannot create node at coordinat ("
      << m_x << "," << m_y << ")"
    ;
    throw std::logic_error(msg.str());
  }
}

void ribi::cmap::CommandSetSelectedWithCoordinat::redo()
{
  m_prev_selected = m_conceptmap->GetSelected();
  m_conceptmap->SetSelected( Nodes( { m_node } ) );
}

void ribi::cmap::CommandSetSelectedWithCoordinat::undo()
{
  //Give back previous selection
  m_conceptmap->SetSelected(m_prev_selected);
}
