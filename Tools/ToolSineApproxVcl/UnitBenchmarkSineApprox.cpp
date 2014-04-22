//---------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>
#include <boost/timer.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
const double Sin_approx(const double x, const double a, const double b, const double c)
{
  const double ranged_x = std::fmod( (2.0 * M_PI) + std::fmod(x,2.0 * M_PI) , 2.0 * M_PI);
  assert(ranged_x >= 0.0);
  assert(ranged_x <= 2.0 * M_PI);
  if (ranged_x < M_PI)
  {
    return (a * ranged_x * ranged_x) + ( b* ranged_x) + c;
  }
  else
  {
    const double reranged_x = ranged_x - M_PI;
    return (-a * reranged_x * reranged_x) + ( -b * reranged_x) - c;
  }

}
//---------------------------------------------------------------------------
const double Sin_approx(const double x)
{
  const double pi_squared = M_PI * M_PI;
  const double a = - 4.0 / pi_squared;
  const double b =   4.0 / M_PI;

  const double ranged_x = std::fmod( (2.0 * M_PI) + std::fmod(x,2.0 * M_PI) , 2.0 * M_PI);
  assert(ranged_x >= 0.0);
  assert(ranged_x <= 2.0 * M_PI);
  if (ranged_x < M_PI)
  {
    return (a * ranged_x * ranged_x) + ( b* ranged_x);
  }
  else
  {
    const double reranged_x = ranged_x - M_PI;
    return (-a * reranged_x * reranged_x) + ( -b * reranged_x);
  }

}
//---------------------------------------------------------------------------
int main()
{
  const double d_min = -4.0 * M_PI;
  const double d_max =  4.0 * M_PI;
  const double d_step = (d_max - d_min) / 100000.0;

  double t_sin = 0.0;
  double t_sin_approx = 0.0;

  for (int i=0; i!=100; ++i)
  {
    //std::sin
    {
      double sum = 0.0;

      boost::timer t;
      for (double d=d_min; d<d_max; d+=d_step)
      {
        sum+=std::sin(d);
      }
      const double elapsed = t.elapsed();
      t_sin+=elapsed;
    }
    //Sin_approx
    {
      double sum = 0.0;

      boost::timer t;
      for (double d=d_min; d<d_max; d+=d_step)
      {
        sum+=Sin_approx(d);
      }
      const double elapsed = t.elapsed();
      t_sin_approx+=elapsed;
    }

  }
  std::cout
    << "std::sin: " << t_sin << std::endl
    << "Sin_approx: " << t_sin_approx << std::endl;
  std::cin.get();
}
//---------------------------------------------------------------------------



/*
Calculation

To approximate f(x)=sin(x), for values of x e [0,pi] a parabola can be used.
Like the sine, this parabola passes the following three coordinats:
#1) (0,0)
#2) (0.5 * pi, 1)
#3) (pi,0).

The formula of a parabola can be written down as follows:

f(x) = (A * x * x) + (B * x) + C

Where A,B and C are constants that define the shape of the parabols.

Entering the coordinats in the formula results in the following equations:

#0) hpi = 0.5 * pi (for simpler notation of #2)
#1) 0 = (A * 0   * 0  ) + (B * 0  ) + C
#2) 1 = (A * hpi * hpi) + (B * hpi) + C
#3) 0 = (A * pi  * pi ) + (B * pi ) + C

From #1 follows that C = 0.

This leaves us with two equations (#2 and #3) with two unknown variables.
The commons strategy is as follows:
a) Take one equation
b) Define one variable in terms of the other
c) Use this variable in the other equation
d) Solve the latter equation to find the first variable's value
e) Use the found variable's value to calculate the second

Define one variable in terms of the other:
1 = (A * hpi * hpi) + (B * hpi)
1 - (B * hpi) = (A * hpi * hpi)
- (B * hpi) = (A * hpi * hpi) - 1
- B = (A * hpi) - (1 / hpi)
B = - (A * hpi) + (1 / hpi)

Use this term to calculate the first variable:
0 = (A * pi  * pi ) + (B * pi ) + C
Use B = - (A * hpi) + (1 / hpi)
0 = (A * pi * pi ) + ( (- (A * hpi) + (1 / hpi) ) * pi )
0 = (A * pi * pi ) + ( - (A * hpi * pi) + (1 * pi / hpi) )
0 = (A * pi * pi ) - (A * hpi * pi) + (1 * pi / hpi)
- (1 * pi / hpi) = (A * pi * pi ) - (A * hpi * pi)
- (1 * pi / hpi) = A * ( (pi * pi) - (hpi * pi) )
- (1 * pi / hpi) = A * ( (pi * pi) - ( (0.5 * pi) * pi) )
- (1 * pi / hpi) = A * ( (pi * pi) - ( 0.5 * pi * pi) )
- (1 * pi / hpi) = A * 0.5 * pi * pi
- (1 * pi / ( 0.5 * pi) ) = A * 0.5 * pi * pi
- 2 = A * 0.5 * pi * pi
- 2 / 0.5 * pi * pi = A
A = - 4 / (pi * pi)

Calculate the second variable:
1 = (A * hpi * hpi) + (B * hpi)
Use A = - 4 / (pi * pi)
1 = ( (- 4 / (pi * pi) ) * hpi * hpi) + (B * hpi)
- (B * hpi) + 1 = ( (- 4 / (pi * pi) ) * hpi * hpi)
- (B * hpi) = ( (- 4 / (pi * pi) ) * hpi * hpi) - 1
- (B * hpi) = ( (- 4 * (hpi * hpi) / (pi * pi) ) ) - 1
- (B * hpi) = ( (- 4 * 0.5 * pi * 0.5 * pi) / (pi * pi) ) - 1
- (B * hpi) = ( (- 1 * pi * pi) / (pi * pi) ) - 1
- (B * hpi) = - 1 - 1
- (B * hpi) = - 2
- B * 0.5 * pi = - 2
B * 0.5 * pi = 2
B  = 2 / (0.5 * pi)
B  = 4 / pi

Conclusion:
A = - 4 / (pi * pi)
B  = 4 / pi

So
f(x) = ((- 4 / (pi * pi)) * x * x) + ( (4 / pi) * x)
f(x) = ( (- 4 * x * x) / (pi * pi) ) + ( (4 * x) / pi )



*/

 