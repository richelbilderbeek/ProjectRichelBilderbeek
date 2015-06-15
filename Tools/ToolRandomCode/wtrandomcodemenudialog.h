//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#ifndef WTRANDOMCODEMENUDIALOG_H
#define WTRANDOMCODEMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#pragma GCC diagnostic pop

namespace Wt
{
  struct WWidget;
}

namespace ribi {

struct WtAboutDialog;
struct WtRandomCodeGenerateDialog;

struct WtRandomCodeMenuDialog : public Wt::WContainerWidget
{
  WtRandomCodeMenuDialog();
  private:
  void CheckResources();
  WtAboutDialog * CreateNewAboutDialog();
  WtRandomCodeGenerateDialog * CreateNewGenerateDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};

} //~namespace ribi

#endif // WTRANDOMCODEMENUDIALOG_H
