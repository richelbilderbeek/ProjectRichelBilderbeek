#include "searchanddestroychessmenudialog.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "chessgame.h"

#include "chesswidget.h"
#include "chesssquareselector.h"
#include "chesssquarefactory.h"
#include "chesssquare.h"
#include "chessscore.h"
#include "chessrank.h"
#include "chessplayer.h"
#include "chesspiecefactory.h"
#include "chesspiece.h"
#include "chessmoves.h"
#include "chessmovefactory.h"
#include "chessmove.h"
#include "chesshelper.h"
#include "chessgamewidget.h"
#include "chessgame.h"
#include "chessfwd.h"
#include "chessfile.h"
#include "chesscolor.h"
#include "chesscastling.h"
#include "chessboardwidget.h"
#include "chessboardfactory.h"
#include "chessboard.h"
#include "chessbitboard.h"

#include "richelbilderbeekprogram.h"
#include "trace.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::sadc::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::sadc::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}


ribi::About ribi::sadc::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SearchAndDestroyChess",
    "Kriegspiel",
    "the 23rd of Februari 2013",
    "2011-2015",
    "http://www.richelbilderbeek.nl/GameSearchAndDestroyChess.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Artwork from GNU XBoard");
  a.AddLibrary("Chess::widget version: " + Chess::ChessWidget::GetVersion());
  a.AddLibrary("Chess::SquareSelector version: " + Chess::SquareSelector::GetVersion());
  a.AddLibrary("Chess::Square: " + Chess::Square::GetVersion());
  a.AddLibrary("Chess::Score: " + Chess::Score::GetVersion());
  a.AddLibrary("Chess::Rank: " + Chess::Rank::GetVersion());
  a.AddLibrary("Chess::Moves: " + Chess::Moves::GetVersion());
  a.AddLibrary("Chess::Move: " + Chess::Move::GetVersion());
  a.AddLibrary("Chess::Game: " + Chess::Game::GetVersion());
  a.AddLibrary("Chess::GameWidget: " + Chess::GameWidget::GetVersion());
  a.AddLibrary("Chess::File: " + Chess::File::GetVersion());
  a.AddLibrary("Chess::Board: " + Chess::Board::GetVersion());
  a.AddLibrary("Chess::BoardWidget: " + Chess::BoardWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::sadc::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::sadc::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramSearchAndDestroyChess
  };
  assert(p);
  return p;
}


std::string ribi::sadc::MenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::sadc::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-28: Version 1.0: initial version",
    "2013-02-24: Version 1.1: testing done in seperate thread"
  };
}

#ifndef NDEBUG
void ribi::sadc::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    MenuDialog();
    Chess::Game();
  }
}
#endif
