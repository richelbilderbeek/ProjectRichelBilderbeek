#ifndef NDEBUG
#include "qtmutualismbreakdownertimeplotdialog.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "fileio.h"

void ribi::mb::QtMutualismBreakdownerTimePlotDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  {
    QtMutualismBreakdownerTimePlotDialog d;
    Parameters parameters;
    d.SetParameters(parameters);
    if (d.GetParameters() != parameters)
    {
      std::cerr << d.GetParameters() << '\n'
        << parameters << '\n'
      ;
    }
    assert(d.GetParameters() == parameters);
  }
}
#endif


