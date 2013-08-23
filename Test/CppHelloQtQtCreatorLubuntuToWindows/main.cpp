//---------------------------------------------------------------------------
/*
CppHelloQtQtCreatorLubuntu, Hello World program using Qt Creator under Lubuntu
Copyright (C) 2013  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppHelloQtQtCreatorLubuntu.htm
//---------------------------------------------------------------------------
//Support both Qt4 and Qt5
#include <qglobal.h>
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  #include <QApplication>
#else
  #include <QApplication>
#endif

#include "dialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Dialog w;
  w.show();
  return a.exec();
}

