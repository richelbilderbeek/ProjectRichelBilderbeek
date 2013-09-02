//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

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

#include <QDialog>
#include "richelbilderbeekprogramtype.h"
#include "qthideandshowdialog.h"

struct QtRichelBilderbeekProgram
{
  ///Create the menu dialog corresponding to the program type
  ///Might return a nullprt, if the program type has no Qt menu
  static QDialog * CreateQtMenuDialog(const RichelBilderbeek::ProgramType type);

  ///Create a placeholder dialog for the program type
  static QtHideAndShowDialog * CreateQtPlaceholderDialog(const RichelBilderbeek::ProgramType type);

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  static bool IsRegularFile(const std::string& filename);
};

#endif // QTRICHELBILDERBEEKPROGRAM_H
