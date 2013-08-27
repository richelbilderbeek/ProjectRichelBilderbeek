///Adapted from http://www.alglib.net/translator/man/manual.cpp.html#lsfit_d_lin%20example

#include <cassert>
#include <iostream>
#include "interpolation.h"

int main()
{
  //
  // In this example we demonstrate linear fitting by f(x|a) = a*exp(0.5*x).
  //
  // We have:
  // * y - vector of experimental data
  // * fmatrix -  matrix of basis functions calculated at sample points
  //              Actually, we have only one basis function F0 = exp(0.5*x).
  //
  const alglib::real_2d_array fmatrix = "[[0.606531],[0.670320],[0.740818],[0.818731],[0.904837],[1.000000],[1.105171],[1.221403],[1.349859],[1.491825],[1.648721]]";
  const alglib::real_1d_array y = "[1.133719, 1.306522, 1.504604, 1.554663, 1.884638, 2.072436, 2.257285, 2.534068, 2.622017, 2.897713, 3.219371]";
  alglib::ae_int_t info;
  alglib::real_1d_array c;
  alglib::lsfitreport rep;

  //
  // Linear fitting without weights
  //

  alglib::lsfitlinear(y, fmatrix, info, c, rep);

  assert(info == 1);
  assert(c.tostring(4) == std::string("[1.9865]"));
}
