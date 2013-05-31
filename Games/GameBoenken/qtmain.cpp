//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2012 Richel Bilderbeek

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
#include <QtGui/QApplication>
#include "qtboenkenmenudialog.h"
//---------------------------------------------------------------------------
/// \mainpage Boenken documentation
///
/// Boenken is a simple game
///
/// Boenken version 4.0\n
/// (C) 2005-2012 Richel Bilderbeek\n
/// programmed on the 6th of March of 2012\n
/// From http://www.richelbilderbeek.nl/GameBoenken.htm\n
/// Licenced under GPL 3.0\n
///
/// \author  Richel Bilderbeek
/// \version 4.0
/// \date    2012-03-06
//---------------------------------------------------------------------------
///Only shows the menu
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  a.setStyleSheet(
    "QDialog { "
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #FF9090, stop: 1 #9090FF);"
    "}"
  );

  QtBoenkenMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
