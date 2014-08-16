#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "reversimaindialog.h"

#include <iostream>
#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include "reversiboard.h"
#include "reversiwidget.h"
#include "reversimove.h"
#include "fileio.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::reversi::MainDialog::MainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::reversi::MainDialog::Execute(const int size)
{
  Widget w(size);
  while (1)
  {
    std::cout
      << w << '\n'
      << '\n'
      << "Please enter a move: ";
    std::string s;
    std::cin >> s;
    if (s == "quit" || s == "bye" || s == "exit") return;
    if (s == "Hint" || s == "hint" || s == "h" || s == "H" || s == "?")
    {
      std::cout << '\n'
        << "List of all possible moves:\n";
      for (const boost::shared_ptr<Move> move: w.GetValidMoves())
      {
        std::cout << move->ToStr() << '\n';
      }
      std::cout << '\n';
      continue;
    }
    const boost::shared_ptr<Move> move { Move::Parse(s) };
    if (!move)
    {
      std::cout << "Invalid move. Possible input:\n"
        << "x,y : put a piece at coordinat x,y, for example '0,0'\n"
        << "p: pass\n"
        << "h: hint: obtain all possible moves\n"
        << "quit: quit game\n"
        << '\n';
      continue;
    }
    if (!w.CanDoMove(move))
    {
      std::cout << "Move is not allowed\n"
        << '\n';
      continue;
    }
    w.DoMove(move);
  }
}

#ifndef NDEBUG
void ribi::reversi::MainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  Board();
  Widget();
}
#endif
