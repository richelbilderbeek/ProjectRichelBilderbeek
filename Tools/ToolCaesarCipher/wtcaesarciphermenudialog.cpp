//---------------------------------------------------------------------------
/*
CaesarCipher, tool to test the CaesarCipher class
Copyright (C) 2009-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CaesarCipher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <cassert>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WWidget>

#include "about.h"
#include "caesarciphermenudialog.h"
#include "wtautoconfig.h"
#include "wtaboutdialog.h"
#include "wtcaesarciphermaindialog.h"
#include "wtcaesarciphermenudialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::WtCaesarCipherMenuDialog::WtCaesarCipherMenuDialog()
{
  //Create resources
  {
    std::vector<std::string> image_names;
    image_names.push_back("CaesarCipherArrowDown16x16.png");
    image_names.push_back("CaesarCipherArrowDown34x34.png");
    image_names.push_back("CaesarCipherArrowUp16x16.png");
    image_names.push_back("CaesarCipherArrowUp34x34.png");
    image_names.push_back("CaesarCipherWelcome.png");
    BOOST_FOREACH(const std::string& filename,image_names)
    {
      if (!(QFile::exists(filename.c_str())))
      {
        QFile f( (std::string(":/images/") + filename).c_str() );
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
    Wt::WLabel * const title = new Wt::WLabel("CaesarCipher");
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

Wt::WWidget * ribi::WtCaesarCipherMenuDialog::CreateNewAboutDialog() const
{
  About a = CaesarCipherMenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtCaesarCipherMenuDialog::CreateNewMainDialog() const
{
  WtCaesarCipherMainDialog * const d = new WtCaesarCipherMainDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtCaesarCipherMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to CaesarCipher",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("CaesarCipher demonstrates the CaesarCipher encryption and de-encryption algorithm",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
  box->addWidget(new Wt::WImage("CaesarCipherWelcome.png"));
  return dialog;
}

