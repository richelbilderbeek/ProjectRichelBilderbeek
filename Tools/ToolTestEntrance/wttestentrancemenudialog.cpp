//---------------------------------------------------------------------------
/*
TestEntrance, tool to test WtEntrance
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "testentrancemenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wttestentrancemaindialog.h"
#include "wttestentrancemenudialog.h"
#include "wtentrance.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::ToolTestEntrance::WtMenuDialog::WtMenuDialog(
  boost::shared_ptr<const IpAddress> ip_address)
{
  {
    std::vector<std::string> image_names;
    image_names.push_back("ToolTestEntranceWelcome.png");

    BOOST_FOREACH(const std::string& filename,image_names)
    {
      if (!(QFile::exists(filename.c_str())))
      {
        QFile f( (std::string(":/ToolTestEntrance/images/") + filename).c_str() );
        f.copy(filename.c_str());
      }
      if (!boost::filesystem::exists(filename.c_str()))
      {
        std::cerr << "File not found: " << filename << '\n';
      }
      assert(boost::filesystem::exists(filename.c_str()));
    }
  }

  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TestEntrance");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
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
        CreateNewMainDialog(ip_address));
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

Wt::WWidget * ribi::ToolTestEntrance::WtMenuDialog::CreateNewAboutDialog()
{
  About a = MenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtEntrance version: " + WtEntrance::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::ToolTestEntrance::WtMenuDialog::CreateNewMainDialog(boost::shared_ptr<const IpAddress> ip_address) const
{
  WtMainDialog * const d = new WtMainDialog(ip_address);
  assert(d);
  return d;
}

Wt::WWidget * ribi::ToolTestEntrance::WtMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to TestEntrance",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("TestEntrance demonstrates the WtEntrance class",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolTestEntranceWelcome.png"));
  return dialog;
}
