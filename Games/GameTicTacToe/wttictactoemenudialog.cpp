//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
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
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#include "wttictactoemenudialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>

#include "about.h"
#include "tictactoemenudialog.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wttictactoegamedialog.h"
#include "wttictactoewidget.h"
#pragma GCC diagnostic pop

ribi::tictactoe::WtTicTacToeMenuDialog::WtTicTacToeMenuDialog()
{
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("TicTacToe");
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
        "Start",
        new WtTicTacToeGameDialog(false));
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

ribi::WtAboutDialog * ribi::tictactoe::WtTicTacToeMenuDialog::CreateNewAboutDialog() const
{
  About a = tictactoe::TicTacToeMenuDialog().GetAbout();
  a.AddLibrary("WtTicTacToeWidget version: " + WtTicTacToeWidget::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  return d;
}


