//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#ifndef QTBOENKENPLAYERSDIALOG_H
#define QTBOENKENPLAYERSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenPlayersDialog;
}

namespace ribi {

///Dialog to connect sprites to their controllers\n
///A controller can be\n
///- a human\n
///- a computer\n
class QtBoenkenPlayersDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtBoenkenPlayersDialog(QWidget *parent = 0);
  QtBoenkenPlayersDialog(const QtBoenkenPlayersDialog&) = delete;
  QtBoenkenPlayersDialog& operator=(const QtBoenkenPlayersDialog&) = delete;
  ~QtBoenkenPlayersDialog() noexcept;

private:
  Ui::QtBoenkenPlayersDialog *ui;
};

} //~namespace ribi

#endif // QTBOENKENPLAYERSDIALOG_H
