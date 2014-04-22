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
#ifndef QTRICHELBILDERBEEKPROGRAM_H
#define QTRICHELBILDERBEEKPROGRAM_H

#include "qthideandshowdialog.h"
#include "richelbilderbeekprogramtype.h"
#include "qthideandshowdialog.h"

namespace ribi {

struct QtRichelBilderbeekProgram
{
  ///Create the menu dialog corresponding to the program type
  ///Might return a nullprt, if the program type has no menu
  static QtHideAndShowDialog * CreateQtMenuDialog(const ProgramType type);

  ///Create a placeholder dialog for the program type
  static QtHideAndShowDialog * CreateQtPlaceholderDialog(const ProgramType type);
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKPROGRAM_H
