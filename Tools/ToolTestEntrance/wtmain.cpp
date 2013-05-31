//---------------------------------------------------------------------------
/*
TestEntrance, tool to test WtEntrance
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestEntrance.htm
//---------------------------------------------------------------------------
#include <iostream>

#include <boost/program_options.hpp>

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WText>

#include "ipaddress.h"
#include "wttestentrancemenudialog.h"
#include "wtautoconfig.h"
#include "wtentrance.h"

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
  : WApplication(env)
  {
    setTitle("TestEntrance");
    this->useStyleSheet("wt.css");
    boost::shared_ptr<const IpAddress> ip_address(new IpAddress(env.clientAddress()));
    WtEntrance::Get()->Visit(ip_address.get());
    root()->addWidget(new ToolTestEntrance::WtMenuDialog(ip_address));
  }
};

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{

  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  WtAutoConfig::SaveDefaultStylesheet();
  WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}

