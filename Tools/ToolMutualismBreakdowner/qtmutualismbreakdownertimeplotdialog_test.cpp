#ifndef NDEBUG
#include "qtmutualismbreakdownertimeplotdialog.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

void QtMutualismBreakdownerTimePlotDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  Parameters parameters; parameters.SetRandom();
  {
    QtMutualismBreakdownerTimePlotDialog d;
    d.SetParameters(parameters);
    assert(d.GetParameters() == parameters);
  }
}
#endif


