//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#include <QtGui/QApplication>
#include "qtpylosmenudialog.h"
#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"
#include "trace.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();

  Pylos::Board::Test();
  Pylos::Coordinat::Test();
  Pylos::CurrentMoveState::Test();
  Pylos::Game::Test();
  Pylos::Move::Test();

  QtPylosMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
