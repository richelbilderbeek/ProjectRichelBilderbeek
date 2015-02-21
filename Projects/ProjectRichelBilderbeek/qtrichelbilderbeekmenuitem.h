//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#ifndef QTRICHELBILDERBEEKMENUITEM_H
#define QTRICHELBILDERBEEKMENUITEM_H

#include "richelbilderbeekprogramtype.h"
//#include "qtroundedtextrectitem.h" //OBSOLETE
#include "qtroundededitrectitem.h"

namespace ribi {

struct QtRichelBilderbeekMenuItem : public QtRoundedEditRectItem
{
  QtRichelBilderbeekMenuItem(const ProgramType program_type);

  ProgramType GetProgramType() const noexcept { return m_program_type; }

  const ProgramType m_program_type;
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKMENUITEM_H
