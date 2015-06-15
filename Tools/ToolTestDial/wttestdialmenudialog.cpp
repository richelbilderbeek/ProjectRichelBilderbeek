//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "rainbow.h"
#include "testdialmenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtdialwidget.h"
#include "wttestdialmaindialog.h"
#include "wttestdialmenudialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::WtTestDialMenuDialog::WtTestDialMenuDialog()
{
  //Create resources
  {
    const std::vector<std::string> image_names
      =
    {
      "ToolTestDialWelcome_2_1.png"
    };
    std::for_each(image_names.begin(),image_names.end(),
      [](const std::string& filename)
      {
        if (!(QFile::exists(filename.c_str())))
        {
          QFile f( (std::string(":/ToolTestDial/images/") + filename).c_str() );
          f.copy(filename.c_str());
        }
        if (!QFile::exists(filename.c_str()))
        {
          const std::string s = "File not found: " + filename;
          throw std::logic_error(s.c_str());
        }
        assert(QFile::exists(filename.c_str()));
      }
    );
  }

  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TestDial");
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

Wt::WWidget * ribi::WtTestDialMenuDialog::CreateNewAboutDialog() const
{
  About a = TestDialMenuDialog().GetAbout();
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtDialWidget version: " + WtDialWidget::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestDialMenuDialog::CreateNewMainDialog() const
{
  WtTestDialMainDialog * const d = new WtTestDialMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestDialMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to TestDial",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("TestDial tests and displays the Dial class",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolTestDialWelcome_2_1.png"));

  return dialog;
}

