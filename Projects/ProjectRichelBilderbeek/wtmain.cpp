//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "ipaddress.h"
#include "trace.h"
#include "wtautoconfig.h"
#include "wtentrance.h"
#include "wtselectfiledialog.h"
#include "wtrichelbilderbeekmenudialog.h"

///TODO
///List sorted on my priority
/// - Add an IP-address/'personal' page
/// - Add SearchAndDestroyChess
/// - Add TestCss to change IP-address/'personal' CSS
/// - Let all WtRichelBilderbeek classes be documented using Doxygen
/// - Test Wt real-time gaming possibilities

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("Project Richel Bilderbeek");
    this->useStyleSheet("wt.css");
    this->enableUpdates(true);
    boost::shared_ptr<const ribi::IpAddress> ip_address(new ribi::IpAddress(env.clientAddress()));
    ribi::WtEntrance::Get()->Visit(ip_address.get());
    root()->addWidget(new ribi::RichelBilderbeek::WtMenuDialog(ip_address->Get()));
  }
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  START_TRACE();
  ribi::WtSelectFileDialog::SetPath(boost::filesystem::path(argv[0]).parent_path().string());
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  ribi::WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}
