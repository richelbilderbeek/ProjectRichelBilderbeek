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
#include "conceptmapcommand.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic pop

#include "trace.h"

ribi::cmap::Command::Command() noexcept
  : m_signal_undo{}
{

}

bool ribi::cmap::Command::CanDoCommand(const ConceptMap * const widget) const noexcept
{
  assert(widget);
  return CanDoCommandSpecific(widget);
}

void ribi::cmap::Command::DoCommand(ConceptMap * const widget) noexcept
{
  assert(widget);
  assert(CanDoCommand(widget));
  DoCommandSpecific(widget);
  /*
  #ifndef NDEBUG
  for (int i=0; i!=2; ++i)
  {
    Undo();
    DoCommandSpecific(widget);
  }
  #endif
  */
}

void ribi::cmap::Command::Undo() noexcept
{
  UndoSpecific();
  m_signal_undo(this);
}
