#ifndef NDEBUG
#include "qtpoisoningfunctionwidget.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "fileio.h"
#include "parameters.h"
#include "poisoningfunction.h"

void QtPoisoningFunctionWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  {
    QtPoisoningFunctionWidget d;
    const Parameters parameters;
    const auto f = parameters.poisoning_function;
    d.SetFunction(f);
    if (d.GetFunction()->ToStr() != f->ToStr())
    {
      std::cerr << d.GetFunction()->ToStr() << '\n'
        << f->ToStr() << '\n'
      ;
    }
    assert(d.GetFunction()->ToStr() == f->ToStr());
  }
}
#endif



