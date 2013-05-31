//---------------------------------------------------------------------------
/*
TicTacToeLearner, evolving neural network playing tic-tac-toe
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
#include <QtGui/QApplication>
#include "dialog.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  #ifdef NDEBUG
    std::clog << "main() debugging disabled\n";
    assert(1==2 && !"Nonsense can now be written");
  #endif
  QApplication a(argc, argv);
  Dialog d;
  d.show();
  return a.exec();
}
//---------------------------------------------------------------------------
