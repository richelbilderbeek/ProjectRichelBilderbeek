//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#ifndef WTPICTOCODEMENUDIALOG_H
#define WTPICTOCODEMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtAboutDialog;

namespace p2c {

struct WtMenuDialog : public Wt::WContainerWidget
{
  WtMenuDialog();

  private:
  WtAboutDialog * CreateNewAboutDialog() const;
};

} //~namespace p2c
} //~namespace ribi

#endif // WTPICTOCODEMENUDIALOG_H
