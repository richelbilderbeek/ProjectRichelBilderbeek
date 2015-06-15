//---------------------------------------------------------------------------
/*
TestSelectFileDialog, tool to test the SelectFileDialog class
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
//From http://www.richelbilderbeek.nl/ToolTestSelectFileDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "trace.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtselectfiledialog.h"
#include "wttestselectfiledialogmaindialog.h"
#include "wttestselectfiledialogmenudialog.h"

#pragma GCC diagnostic pop

ribi::WtTestSelectFileDialogMenuDialog::WtTestSelectFileDialogMenuDialog()
{
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TestSelectFileDialog");
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

Wt::WWidget * ribi::WtTestSelectFileDialogMenuDialog::CreateNewAboutDialog() const
{
   About a(
    "Richel Bilderbeek",
    "TestSelectFileDialog",
    "tool to test the SelectFileDialog class",
    "the 15th of July 2011",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestSelectFileDialog.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtSelectFileDialog version: " + WtSelectFileDialog::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestSelectFileDialogMenuDialog::CreateNewMainDialog() const
{
  WtTestSelectFileDialogMainDialog * const d
    = new WtTestSelectFileDialogMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestSelectFileDialogMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to TestSelectFileDialog",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("TestSelectFileDialog tests the WtSelectFileDialog class:",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  Wt::WImage * const image = new Wt::WImage("ToolTestSelectFileDialogWelcome.png");
  box->addWidget(image);
  return dialog;
}

std::string ribi::WtTestSelectFileDialogMenuDialog::GetVersion()
{
  return "1.1";
}

std::vector<std::string> ribi::WtTestSelectFileDialogMenuDialog::GetVersionHistory()
{
  return {
    "2011-07-01: Version 1.0: initial version",
    "2011-07-15: Version 1.1: added downloading of selected files"
  };
}

