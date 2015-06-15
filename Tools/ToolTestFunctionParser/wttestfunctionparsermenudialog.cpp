//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <cassert>

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "fileio.h"
#include "testfunctionparsermenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wttestfunctionparsermaindialog.h"
#include "wttestfunctionparsermenudialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::WtTestFunctionParserMenuDialog::WtTestFunctionParserMenuDialog()
{
  {
    std::vector<std::string> image_names;
    image_names.push_back("ToolTestFunctionParserWelcome.png");

    for(const std::string& filename: image_names)
    {

      if (!(ribi::fileio::FileIo().IsRegularFile(filename)))
      {
        QFile f( (std::string(":/ToolTestFunctionParser/images/") + filename).c_str() );
        f.copy(filename.c_str());
      }
      if (!ribi::fileio::FileIo().IsRegularFile(filename))
      {
        std::cerr << "File not found: " << filename << '\n';
      }
      assert(ribi::fileio::FileIo().IsRegularFile(filename));
    }
  }
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TestFunctionParser");
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

Wt::WWidget * ribi::WtTestFunctionParserMenuDialog::CreateNewAboutDialog() const
{
  About a = TestFunctionParserMenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestFunctionParserMenuDialog::CreateNewMainDialog() const
{
  WtTestFunctionParserMainDialog * const d = new WtTestFunctionParserMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtTestFunctionParserMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to TestFunctionParser",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("TestFunctionParser tests and demonstrates Warp's FunctionParser class",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Warp's FunctionParser class can be downloaded from",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("http://warp.povusers.org/FunctionParser",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolTestFunctionParserWelcome.png"));
  return dialog;
}

