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

#include <boost/shared_ptr.hpp>

#include <QIcon>
#include <QFile>
#include <QPixmap>
#include "qtk3opeenrijresources.h"
#include "qtk3opeenrijmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

const std::string CreateStyleSheet()
{
  const std::string s =
    "QDialog { "
    "  background-image: url(:/images/PicLoomBackground.png);"
//    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bbf, stop: 1 #bff);"
    "} "
    "QLabel { "
    "  font-size: 18px;"
    "  font-family: \"Courier\", \"Courier New\", Courier, monospace;"
    "  font-weight: bold;"
    "  padding: 1px;"
    "} "
    ""
    "QPushButton {"
    "  font-family: \"Courier New\", \"Courier\", Courier, monospace;"
    "  font-size: 16px;"
    "  border-width: 1px;"
    "  border-style: solid;"
    "  padding: 3px;"
    "} "
    ""
    "QPushButton:enabled {"
    "  color: black;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);"
    "  border-color: #111;"
    "} "
    "QPushButton:disabled {"
    "  color: #888;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);"
    "  border-color: #fff;"
    "} "
    ""
    "QPlainTextEdit {"
    "  font-size: 12px;  font-family: \"Courier\", \"Courier New\", Courier, monospace;"
    "}";

  return s;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  START_TRACE();
  const boost::shared_ptr<const ribi::QtK3OpEenRijResources> resources(new ribi::QtK3OpEenRijResources);
  ribi::QtK3OpEenRijMenuDialog w(resources);

  {
    const ribi::QtK3OpEenRijResources resources2;
    const std::string icon_filename = resources2.GetIconFilename();
    assert(QFile::exists(icon_filename.c_str()));
    qApp->setWindowIcon(QIcon(QPixmap(icon_filename.c_str())));
    w.setWindowIcon(QIcon(QPixmap(icon_filename.c_str())));
  }

  w.show();
  return a.exec();
}
