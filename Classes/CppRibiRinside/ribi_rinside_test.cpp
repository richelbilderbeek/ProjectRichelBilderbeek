#ifndef NDEBUG

#include "ribi_rinside.h"
#include "RInside.h"

#include <cassert>

void ribi::Rinside::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  auto& r = Rinside().Get();
  //Read/write of integer
  {
    r["x"] = 42;
    Rcpp::NumericVector v = r.parseEval("x");
    assert(v.size() == 1);
    assert(v[0] == 42);
  }
}

#endif // NDEBUG
