#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testreversimaindialog.h"

#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include "reversi.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestReversiMainDialog::TestReversiMainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::TestReversiMainDialog::Execute()
{

}

#ifndef NDEBUG
void ribi::TestReversiMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestReversiMenuDialog::Test()");
  TRACE("Finished ribi::TestReversiMenuDialog::Test()");
}
#endif
