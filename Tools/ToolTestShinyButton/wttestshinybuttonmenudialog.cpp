//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
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
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "wttestshinybuttonmenudialog.h"

#include <cassert>

////#include <boost/filesystem.hpp>

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include <QFile>

#include "fileio.h"
#include "rainbow.h"
#include "testshinybuttonmenudialog.h"
#include "shinybutton.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtshinybuttonwidget.h"
#include "wtdialwidget.h"
#include "wttestshinybuttonmaindialog.h"

#pragma GCC diagnostic pop

ribi::WtTestShinyButtonMenuDialog::WtTestShinyButtonMenuDialog()
{
  //Create resources
  {
    std::vector<std::string> image_names;
    image_names.push_back("ToolTestShinyButtonWelcome.png");

    for(const std::string& filename: image_names)
    {

      if (!fileio::FileIo().IsRegularFile(filename))
      {
        QFile f( (std::string(":/images/") + filename).c_str() );
        f.copy(filename.c_str());
      }
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        std::cerr << "File not found: " << filename << '\n';
      }
      assert(fileio::FileIo().IsRegularFile(filename));
    }
  }

  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TestShinyButton");
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

Wt::WWidget * ribi::WtTestShinyButtonMenuDialog::CreateNewAboutDialog() const
{
  About a = TestShinyButtonMenuDialog().GetAbout();
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtDialWidget version: " + WtDialWidget::GetVersion());
  a.AddLibrary("WtShinyButtonWidget version: " + WtShinyButtonWidget::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestShinyButtonMenuDialog::CreateNewMainDialog() const
{
  WtTestShinyButtonMainDialog * const d = new WtTestShinyButtonMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestShinyButtonMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to TestShinyButton",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("TestShinyButton tests and displays the ShinyButton and WtShinyButtonWidget classes",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolTestShinyButtonWelcome.png"));
  return dialog;
}

