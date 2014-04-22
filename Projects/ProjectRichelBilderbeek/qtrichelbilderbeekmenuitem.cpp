//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2014 Richel Bilderbeek

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
#include "qtrichelbilderbeekmenuitem.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QPen>

#include "richelbilderbeekprogramtypes.h"
#pragma GCC diagnostic pop

ribi::QtRichelBilderbeekMenuItem::QtRichelBilderbeekMenuItem(const ProgramType program_type)
  : m_program_type(program_type)
{

  QPen pen = GetFocusPen();
  pen.setWidth(3);
  pen.setColor(QColor(255,0,0));
  SetFocusPen(pen);

  this->SetText(ProgramTypes::ProgramTypeToScreenName(program_type));

  //Rotation
  {
    const double f = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    const double angle = -3.0 + (6.0 * f);
    this->setRotation(angle);
  }
}
