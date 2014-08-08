#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testreversimaindialog.h"

#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

#include "reversiboard.h"
#include "fileio.h"
#include "testtimer.h"
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
