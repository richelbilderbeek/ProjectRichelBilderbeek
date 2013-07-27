//---------------------------------------------------------------------------
/*
QtAboutDialog, Qt dialog for About
Copyright (C) 2011-2012 Richel Bilderbeek

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

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <string>
#include <vector>

#include <QDialog>


#include "about.h"

namespace Ui {
  class QtAboutDialog;
}

///An About dialog
class QtAboutDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtAboutDialog(const About& about);
  ~QtAboutDialog();

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtAboutDialog *ui;
};


#endif // QTABOUTDIALOG_H
