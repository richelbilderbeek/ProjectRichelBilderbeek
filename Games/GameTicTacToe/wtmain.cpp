//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
Copyright (C) 2010-2014 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "fileio.h"
#include "wtautoconfig.h"
#include "wttictactoemenudialog.h"

#include <QFile>
#pragma GCC diagnostic pop

struct WtTicTacToeApplication : public Wt::WApplication
{
  WtTicTacToeApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("TicTacToe");
    const std::string css_filename = "GameTicTacToe.css";
    ribi::fileio::FileIo f;
    if (!f.IsRegularFile(css_filename))
    {
      QFile g( (std::string(":/gametictactoe/files/") + css_filename).c_str() );
      g.copy(css_filename.c_str() );
      assert(f.IsRegularFile(css_filename));
    }
    if (!f.IsRegularFile(css_filename))
    {
      const std::string s
        = std::string("File '")
        + css_filename
        + std::string("' not found");
      throw std::runtime_error(s);
    }
    this->useStyleSheet(css_filename);
    root()->addWidget(new ribi::tictactoe::WtTicTacToeMenuDialog);
  }

};

Wt::WApplication * createApplication(
  const Wt::WEnvironment& env)
{
  return new WtTicTacToeApplication(env);
}

int main(int argc, char* argv[])
{
  ribi::WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}

