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
#include "gtstgroupparticipating.h"

///m_group_last_index contains the index given to the last group
int ribi::gtst::GroupParticipating::m_group_last_id = 0;

///Constructor that assigns an ID
ribi::gtst::GroupParticipating::GroupParticipating(Server * const server)
  : Group(server),
    m_id(++m_group_last_id)
{
  assert(m_id > 0);
}

///Reset the m_group_last_id to zero
void ribi::gtst::GroupParticipating::Reset()
{
  m_group_last_id = 0;
}

