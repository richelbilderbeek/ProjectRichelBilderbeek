//---------------------------------------------------------------------------
/*
TimePoll, time polling server
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTimePoll.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "wtautoconfig.h"
#include "wttimepollmenudialog.h"
#pragma GCC diagnostic pop

struct WtTimePollApplication : public Wt::WApplication
{
  WtTimePollApplication(const Wt::WEnvironment& env);
};

WtTimePollApplication::WtTimePollApplication(
  const Wt::WEnvironment& env)
  : WApplication(env)
{
  setTitle("TimePoll");
  this->useStyleSheet("wt.css");
  root()->addWidget(new ribi::ToolTimePoll::WtTimePollMenuDialog);
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  return new WtTimePollApplication(env);
}

int main(int argc, char **argv)
{
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  ribi::WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}

