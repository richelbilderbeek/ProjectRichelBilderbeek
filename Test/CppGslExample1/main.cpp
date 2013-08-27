#include <iostream>
#include <gsl/gsl_sf_bessel.h>

int main ()
{
  const double x = 5.0;
  const double y = gsl_sf_bessel_J0(x);
  std::cout << "J0(" << x << ") = " << y << '\n"
}
