//---------------------------------------------------------------------------
/*
TestBroadcastServer, tool to test WtBroadcastServer
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
//From http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm
//---------------------------------------------------------------------------
#include "testbroadcastserverwtmenudialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "testbroadcastservermenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "testbroadcastserverwtmaindialog.h"
#include "wtbroadcastserver.h"
#include "wtbroadcastserverclient.h"
#pragma GCC diagnostic pop

ribi::ToolTestBroadcastServer::WtMenuDialog::WtMenuDialog()
{
 this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TestBroadcastServer");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    //Using CSS styleclass is the best (only?) way to display the menu well
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Welcome",
        CreateNewWelcomeDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Start",
        CreateNewMainDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "About",
        CreateNewAboutDialog());
      menu->addItem(item);
    }
    //Display menu on top
    this->addWidget(menu);
    this->addWidget(new Wt::WBreak);
    //Display contents below menu
    this->addWidget(contents);
  }
}

Wt::WWidget * ribi::ToolTestBroadcastServer::WtMenuDialog::CreateNewAboutDialog()
{
  About a = MenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtBroadcastServer version: " + WtBroadcastServer::GetVersion());
  a.AddLibrary("WtBroadcastServerClient version: " + WtBroadcastServerClient::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::ToolTestBroadcastServer::WtMenuDialog::CreateNewMainDialog() const
{
  WtMainDialog * const d = new WtMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::ToolTestBroadcastServer::WtMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to TestBroadcastServer",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("TestBroadcastServer demonstrates how to view the same changing info",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("from different browsers and/or computers",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("using the WtBroadcastServer and WtBroadcastServerClient classes",dialog);
  return dialog;
}
