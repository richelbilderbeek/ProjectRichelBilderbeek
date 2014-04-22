//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2014 Richel Bilderbeek

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
#ifndef QTBOENKENPRESSKEYDIALOG_H
#define QTBOENKENPRESSKEYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenPressKeyDialog;
}

namespace ribi {

///QtBoenkenPressKeyDialog asks the user to press
///any key. The key pressed can be requested
///later, by DialogControls.
class QtBoenkenPressKeyDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtBoenkenPressKeyDialog(QWidget *parent = 0);
  QtBoenkenPressKeyDialog(const QtBoenkenPressKeyDialog&) = delete;
  QtBoenkenPressKeyDialog& operator=(const QtBoenkenPressKeyDialog&) = delete;
  ~QtBoenkenPressKeyDialog() noexcept;
  int GetKey() const { return m_key; }

protected:
  void keyPressEvent(QKeyEvent * e);

private:
  Ui::QtBoenkenPressKeyDialog *ui;
  int m_key;
};

} //~namespace ribi

#endif // QTBOENKENPRESSKEYDIALOG_H
