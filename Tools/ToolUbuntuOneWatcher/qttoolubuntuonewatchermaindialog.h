//---------------------------------------------------------------------------
/*
UbuntuOneWatcher, tool to see what Ubuntu One is doing
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolUbuntuOneWatcher.htm
//---------------------------------------------------------------------------
#ifndef QTTOOLUBUNTUONEWATCHERMAINDIALOG
#define QTTOOLUBUNTUONEWATCHERMAINDIALOG

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtUbuntuOneWatcherMainDialog;
}

namespace ribi {

class QtUbuntuOneWatcherMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtUbuntuOneWatcherMainDialog(QWidget *parent = 0);
  QtUbuntuOneWatcherMainDialog(const QtUbuntuOneWatcherMainDialog&) = delete;
  QtUbuntuOneWatcherMainDialog& operator=(const QtUbuntuOneWatcherMainDialog&) = delete;
  ~QtUbuntuOneWatcherMainDialog() noexcept;

private:
  Ui::QtUbuntuOneWatcherMainDialog *ui;

private slots:
  void OnFindOut();
};

} //~namespace ribi

#endif // QTTOOLUBUNTUONEWATCHERMAINDIALOG
