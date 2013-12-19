#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "reversimaindialog.h"

#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include "reversiboard.h"
#include "reversiwidget.h"
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
    std::cin >>
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
