///Adapted from http://www.alglib.net/translator/man/manual.cpp.html#lsfit_d_lin%20example

#include <cassert>
#include <iostream>
#include "interpolation.h"

///Result should be {a,b}, as a linear trendline has the equation
///y = a.x + b, but I could not find out how to obtain b
std::pair<double,double> FitLinear(
  const std::vector<double>& xs,
  const std::vector<double>& ys)
{
  alglib::real_1d_array y;
  y.setcontent(ys.size(), &ys[0]);

  alglib::real_2d_array fmatrix;
  fmatrix.setcontent(xs.size(),1,&xs[0]);

  alglib::ae_int_t info;
  alglib::real_1d_array c;
  alglib::lsfitreport rep;

  alglib::lsfitlinear(y, fmatrix, info, c, rep);

  assert(info == 1 && "task is solved successfully");

  ///Result should be {a,b}, as a linear trendline has the equation
  ///y = a.x + b, but I could not find out how to obtain b
  return std::make_pair(c[0],c[0]);
}

int main()
{
  const std::vector<double> x { 0.606531,0.670320,0.740818,0.818731,0.904837,1.000000,1.105171,1.221403,1.349859,1.491825,1.648721 };
  const std::vector<double> y { 1.133719, 1.306522, 1.504604, 1.554663, 1.884638, 2.072436, 2.257285, 2.534068, 2.622017, 2.897713, 3.219371 };
  const std::pair<double,double> p = FitLinear(x,y);

  assert(p.first > 1.98650 && p.first < 1.98651);
  assert(p.second > 1.98650 && p.second < 1.98651);
}
