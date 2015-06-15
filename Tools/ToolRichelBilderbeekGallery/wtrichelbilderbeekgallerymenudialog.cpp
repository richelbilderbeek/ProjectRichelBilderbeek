//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>

#include "about.h"
#include "fileio.h"
#include "richelbilderbeekgallerymenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtrichelbilderbeekgallerydialog.h"
#include "wtrichelbilderbeekgallerymenudialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::WtRichelBilderbeekGalleryMenuDialog::WtRichelBilderbeekGalleryMenuDialog()
{
  {
    std::vector<std::string> image_names;
    image_names.push_back("ToolRichelBilderbeekGallery_1_0.png");
    //image_names.push_back("ToolRichelBilderbeekGalleryWelcome.png");

    for(const auto filename: image_names)
    {

      if (!ribi::fileio::FileIo().IsRegularFile(filename))
      {
        QFile f( (std::string(":/images/") + filename).c_str() );
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
    Wt::WLabel * const title = new Wt::WLabel("RichelBilderbeekGallery");
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

Wt::WWidget * ribi::WtRichelBilderbeekGalleryMenuDialog::CreateNewAboutDialog() const
{
  About a = ribi::GalleryMenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtRichelBilderbeekGalleryMenuDialog::CreateNewMainDialog() const
{
  ribi::RichelBilderbeek::WtGalleryDialog * const d = new ribi::RichelBilderbeek::WtGalleryDialog;
  assert(d);
  return d;
}

Wt::WWidget * ribi::WtRichelBilderbeekGalleryMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to RichelBilderbeekGallery",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("RichelBilderbeekGallery is a gallery of Richel Bilderbeek's work",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Explanation",dialog);
    box->addWidget(new Wt::WImage("ToolRichelBilderbeekGallery_1_0.png"));
  }
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  return dialog;
}

