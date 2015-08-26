//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#include "wtpictocodemenudialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>

#include "about.h"
#include "pictocodemenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtpictocodemaindialog.h"
//#include "qtsprites.h"
#include <QFile>
#pragma GCC diagnostic pop

ribi::p2c::WtMenuDialog::WtMenuDialog()
{
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("PicToCode");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  new Wt::WBreak(this);
  {
    QFile f(":/images/PicNds14x14.png");
    f.copy("PicNds14x14.png");
  }
  new Wt::WImage("PicNds14x14.png",this);
  {
    QFile f(":/images/PicQt14x14.png");
    f.copy("PicQt14x14.png");
  }
  new Wt::WImage("PicQt14x14.png",this);
  {
    QFile f(":/images/PicTo14x14.png");
    f.copy("PicTo14x14.png");
  }
  new Wt::WImage("PicTo14x14.png",this);
  {
    QFile f(":/images/PicStl14x14.png");
    f.copy("PicStl14x14.png");
  }
  new Wt::WImage("PicStl14x14.png",this);
  new Wt::WBreak(this);
  new Wt::WBreak(this);

  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    //Using CSS styleclass is the best (only?) way to display the menu well
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Start",
        new WtMainDialog);
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

ribi::WtAboutDialog * ribi::p2c::WtMenuDialog::CreateNewAboutDialog() const
{
  About a = MenuDialog().GetAbout();
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  return d;
}

