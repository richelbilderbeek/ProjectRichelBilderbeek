
#include "approximator.h"
#include "canvas.h"

int main()
{
  typedef Approximator<double,int> Approximator_t;

  Approximator_t a;
  a.Add(20, 5);
  a.Add(30,15);
  a.Add(40, 5);
  a.Add(50,15);

  const int max_x = 78;
  const int max_y = 20;
  Canvas c(max_x,max_y,Canvas::ColorSystem::invert,Canvas::CoordinatSystem::graph);
  c.DrawLine(0.0,0.0,max_x,0.0);
  c.DrawLine(0.0,0.0,0.0,max_y);

  //Plot values (note: these won't be visible in Canvas)
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (const auto p: a.Get())
    {
      c.DrawDot(
        static_cast<double>(p.first),
        static_cast<double>(p.second)
      );
    }
  }

  //Plot approximation
  {
    for (int t=0; t != max_x; ++t)
    {
      try
      {
        const double x = static_cast<double>(t);
        const double y = a.Approximate(x);
        c.DrawDot(x,y);
      }
      catch (ExceptionNoExtrapolation<Approximator_t::key_type>& e)
      {

      }
    }
  }
  std::cout << c << std::endl;
}

/* Screen output

TRACE '"Starting Approximator::Test"' line 161 in file '../../Classes/CppApproxi
mator/approximator.h': 'Starting Approximator::Test'
TRACE '"Completed Approximator::Test successfully"' line 172 in file '../../Clas
ses/CppApproximator/approximator.h': 'Completed Approximator::Test successfully'

-
o
o
o
o                            oo                  oo
o                           -do                 -do
o                          -o---               -o-
o                          -- -oo-             --
o                         --   -o-            --
o                       -oo-     -o-        -oo-
o                      -oo-      -oo-      -oo-
o                      --          -o-     --
o                    -o-            --   -o-
o                   -oo-             -- -oo-
o                  od-               -odd-
o                  oo                 -do
o
o
o
Moooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo-

Press <RETURN> to close this window...

*/
