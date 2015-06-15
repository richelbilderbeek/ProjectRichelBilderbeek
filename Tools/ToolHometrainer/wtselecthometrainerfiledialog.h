//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
#ifndef WTSELECTHOMETRAINERFILEDIALOG_H
#define WTSELECTHOMETRAINERFILEDIALOG_H

#include <string>
#include <vector>

#include "wtselectfiledialog.h"

namespace ribi {

struct WtSelectHometrainerFileDialog : public WtSelectFileDialog
{
  WtSelectHometrainerFileDialog();

  ///The virtual method how to select Hometrainer files from a folder
  std::vector<std::string> SelectFiles() const noexcept;


  private:
  ///GetFirstLineFromFile reads the first line from a file
  static std::string GetFirstLineFromFile(const std::string& filename);

};

} //~namespace ribi

#endif // WTSELECTHOMETRAINERFILEDIALOG_H
