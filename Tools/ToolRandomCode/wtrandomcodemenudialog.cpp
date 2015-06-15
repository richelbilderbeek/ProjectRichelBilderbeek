//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

//#include <boost/filesystem.hpp>


#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WText>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>

#include "about.h"
#include "fileio.h"
#include "randomcodemenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtrandomcodemenudialog.h"
#include "wtrandomcodegeneratedialog.h"

//QFile must be #included after Wt header files
#include <QFile>
#pragma GCC diagnostic pop

ribi::WtRandomCodeMenuDialog::WtRandomCodeMenuDialog()
{
  CheckResources();
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WText * const title = new Wt::WText("RandomCode");
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
        CreateNewGenerateDialog());
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

void ribi::WtRandomCodeMenuDialog::CheckResources()
{
 //Create resources
  std::vector<std::string> image_names;
  image_names.push_back("ToolRandomCodeWelcome.png");

  for(const std::string& filename: image_names)
  {

    if (!fileio::FileIo().IsRegularFile(filename))
    {
      QFile f( (std::string(":/images/") + filename).c_str() );
      f.copy(filename.c_str());
    }
    if (!fileio::FileIo().IsRegularFile(filename))
    {
      const std::string s = "File not found: " + filename;
      throw std::logic_error(s.c_str());
    }
    assert(fileio::FileIo().IsRegularFile(filename));
  }
}

ribi::WtAboutDialog * ribi::WtRandomCodeMenuDialog::CreateNewAboutDialog()
{
  About a = RandomCodeMenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

ribi::WtRandomCodeGenerateDialog * ribi::WtRandomCodeMenuDialog::CreateNewGenerateDialog() const
{
  WtRandomCodeGenerateDialog * const d = new WtRandomCodeGenerateDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtRandomCodeMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to RandomCode",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("The goal of RandomCode is to generate random C++ code",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("ToolRandomCodeWelcome.png"));
  return dialog;
}

