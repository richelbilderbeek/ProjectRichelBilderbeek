#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "reversimaindialog.h"

#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include "reversiboard.h"
#include "reversiwidget.h"
#include "reversimove.h"
#include "fileio.h"
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
      << "Please enter a move: ";
    std::string s;
    std::cin >> s;
    if (s == "quit" || s == "bye" || s == "exit") return;
    const boost::shared_ptr<Move> move { Move::Parse(s) };
    if (!move)
    {
      std::cout << "Invalid move. Possible moves:\n"
        << "x,y : put a piece at coordinat x,y\n"
        << "  (no text, just press enter): pass\n"
        << "quit: quit game\n"
        << '\n';
      continue;
    }

  }
}

#ifndef NDEBUG
void ribi::reversi::MainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestReversiMenuDialog::Test()");
  Board();
  Widget();
  TRACE("Finished ribi::TestReversiMenuDialog::Test()");
}
#endif
