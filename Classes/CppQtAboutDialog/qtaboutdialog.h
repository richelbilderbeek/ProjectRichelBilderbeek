//---------------------------------------------------------------------------
/*
QtAboutDialog, Qt dialog for About
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtAboutDialog.htm
//---------------------------------------------------------------------------
#ifndef QTABOUTDIALOG_H
#define QTABOUTDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"

#include "about.h"

#pragma GCC diagnostic pop

namespace Ui {
  class QtAboutDialog;
}

namespace ribi {

///An About dialog
class QtAboutDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAboutDialog(const ribi::About& about) noexcept;
  QtAboutDialog(const QtAboutDialog&) = delete;
  QtAboutDialog& operator=(const QtAboutDialog&) = delete;
  ~QtAboutDialog() noexcept;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

private:
  Ui::QtAboutDialog *ui;
};

} //~namespace ribi

#endif // QTABOUTDIALOG_H
