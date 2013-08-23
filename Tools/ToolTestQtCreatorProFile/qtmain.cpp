//---------------------------------------------------------------------------
/*
TestProFile, tool to test the QtCreatorProFile class
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestProFile.htm
//---------------------------------------------------------------------------
#include <QApplication>
#include "qttestqtcreatorprofilemenudialog.h"
#include "trace.h"

const std::string CreateStyleSheet()
{

  const std::string style_sheet
    =
    "QDialog"
    "{"
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #bbb, stop: 1 #fff);"
    "}"
    ;
  return style_sheet;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setStyleSheet(CreateStyleSheet().c_str());
  START_TRACE();
  QtTestQtCreatorProFileMenuDialog w;
  w.show();
  return a.exec();
}

