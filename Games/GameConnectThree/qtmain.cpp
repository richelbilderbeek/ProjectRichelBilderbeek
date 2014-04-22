//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>

#include "qtconnectthreeresources.h"
#include "qtconnectthreemenudialog.h"
#include "trace.h"

#include <QFile>
#include <QIcon>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  START_TRACE();

  ribi::con3::QtConnectThreeMenuDialog w;
  {
    ribi::con3::QtConnectThreeResources resources;
    const std::string icon_filename = resources.GetIconFilename();
    assert(QFile::exists(icon_filename.c_str()));
    w.setWindowIcon( QIcon( QPixmap(icon_filename.c_str())));
  }
  w.show();
  return a.exec();
}
