//---------------------------------------------------------------------------
/*
Hometrainer, tool to make exercises and tests
Copyright (C) 2009-2011  Richl Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolHometrainer
//---------------------------------------------------------------------------
#include <ctime>
//---------------------------------------------------------------------------
#include <QApplication>
//---------------------------------------------------------------------------
#include "qtmenudialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Start tracing
  START_TRACE();

  //Randomize the timer
  //std::srand(std::time(0));

  QtMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
