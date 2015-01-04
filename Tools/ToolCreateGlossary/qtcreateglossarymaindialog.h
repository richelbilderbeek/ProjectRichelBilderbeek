//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
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
//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm
//---------------------------------------------------------------------------
#ifndef QTCREATEGLOSSARYMAINDIALOG_H
#define QTCREATEGLOSSARYMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtCreateGlossaryMainDialog;
}

namespace ribi {

class QtCreateGlossaryMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtCreateGlossaryMainDialog(QWidget *parent = 0);
  QtCreateGlossaryMainDialog(const QtCreateGlossaryMainDialog&) = delete;
  QtCreateGlossaryMainDialog& operator=(const QtCreateGlossaryMainDialog&) = delete;
  ~QtCreateGlossaryMainDialog() noexcept;

private:
  Ui::QtCreateGlossaryMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTCREATEGLOSSARYMAINDIALOG_H
