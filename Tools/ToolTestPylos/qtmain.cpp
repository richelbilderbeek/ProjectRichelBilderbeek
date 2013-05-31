//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#include <QtGui/QApplication>
#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"
//#include "pylosplayer.h"
//#include "pylospositionstate.h"
//#include "pyloswinner.h"
#include "qttestpylosmenudialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
///TODO
///- allow a Player to pass turn when he/she has no marble
///- add tooltips to widget
///- add investigation of winners
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  QtTestPylosMenuDialog w;

  Pylos::Board::Test();
  Pylos::Coordinat::Test();
  Pylos::CurrentMoveState::Test();
  Pylos::Game::Test();
  Pylos::Move::Test();

  w.show();

  return a.exec();
}
//---------------------------------------------------------------------------
