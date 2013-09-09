//---------------------------------------------------------------------------
/*
K3-Op-Een-Rij. A simple game.
Copyright (C) 2007-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameK3OpEenRij.htm
//---------------------------------------------------------------------------
#include <exception>
#include <iostream>

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "connectthreeresources.h"
#include "wtconnectthreemenudialog.h"
#include "about.h"
#include "connectthree.h"
#include "wtaboutdialog.h"
#include "wtconnectthreewidget.h"

namespace ribi {

struct K3OpEenRijApplication : public Wt::WApplication
{
  K3OpEenRijApplication(
    const Wt::WEnvironment& env,
    const ribi::About& about,
    const ribi::ConnectThreeResources& resources)
    : Wt::WApplication(env)
  {
    this->setTitle("K3OpEenRij (C) 2007-2013 Richel Bilderbeek");
    this->useStyleSheet(resources.GetCss());
    root()->addWidget(new ribi::WtConnectThreeMenuDialog(resources,"K3OpEenRij"));
  }
};

} //namespace ribi

ribi::About CreateAbout()
{
  ribi::About about(
    "Richel Bilderbeek",
    "K3-Op-Een-Rij",
    "Connect-three game with a K3 theme",
    "the 10th of January 2011",
    "2007-2013",
    "http://www.richelbilderbeek.nl/GameK3OpEenRij.htm",
    ribi::WtConnectThreeMenuDialog::GetVersion(),
    ribi::WtConnectThreeMenuDialog::GetVersionHistory());
  about.AddLibrary("Wt version: " + std::string(WT_VERSION_STR));
  about.AddLibrary("ConnectThree version: " + ribi::ConnectThree::GetVersion());
  about.AddLibrary("WtConnectThreeWidget version: " + ribi::WtConnectThreeWidget::GetVersion());
  about.AddLibrary("WtAboutDialog version: " + ribi::WtAboutDialog::GetVersion());
  return about;
}

Wt::WApplication * createApplication(const Wt::WEnvironment& env)
{
  ribi::ConnectThreeResources();
  const ribi::ConnectThreeFilenames filenames(
    "K3OpEenRijBackground.png",
    "K3OpEenRijComputer1.png",
    "K3OpEenRijComputer2.png",
    "K3OpEenRijComputer3.png",
    "K3OpEenRijComputerGrey.png",
    "K3OpEenRij.css",
    "K3OpEenRijEmpty.png",
    "K3OpEenRijPlayer1.png",
    "K3OpEenRijPlayer1Grey.png",
    "K3OpEenRijPlayer2.png",
    "K3OpEenRijPlayer2Grey.png",
    "K3OpEenRijPlayer3.png",
    "K3OpEenRijPlayer3Grey.png");
  return new ribi::K3OpEenRijApplication(env,CreateAbout(),filenames);
}

int main(int argc, char **argv)
{
  try
  {
    return Wt::WRun(argc, argv, &createApplication);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    std::clog << e.what() << '\n';
    std::cout << e.what() << '\n';
    return 1;
  }
}

