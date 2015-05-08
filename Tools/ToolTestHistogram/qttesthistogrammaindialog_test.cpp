#ifndef NDEBUG
#include "qttesthistogrammaindialog.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

void QtTestHistogramMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
}
#endif


