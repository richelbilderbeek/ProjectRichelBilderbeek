#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <iostream>

#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/unit.hpp>

#include "multiapproximator.h"
#include "drawcanvas.h"

#pragma GCC diagnostic pop

int main()
{
  //Use Boost.Units to thoroughly check if Approximation is a good template:
  //If it even compiles with Boost.Units, it probably is
  {
    typedef boost::units::quantity<boost::units::si::time> Time;
    typedef boost::units::quantity<boost::units::si::velocity> Velocity;
    ribi::Approximator<Time,Velocity> a;
    a.Add(0.0 * boost::units::si::second,0.0 * boost::units::si::meters_per_second);
    a.Add(2.0 * boost::units::si::second,2.0 * boost::units::si::meters_per_second);
    const Velocity v = a.Approximate(1.0 * boost::units::si::second);
    assert(v >= 0.99 * boost::units::si::meters_per_second
        && v <= 1.01 * boost::units::si::meters_per_second);
    if (v == 0.0 * boost::units::si::meters_per_second)
    {
      std::cout << "Satisfied the compiler";
    }


  }

  typedef ribi::MultiApproximator<double,double> MultiApproximator_t;

  MultiApproximator_t a;
  a.Add(20.0, 3.0);
  a.Add(20.0, 7.0);
  a.Add(30.0,14.0);
  a.Add(30.0,16.0);
  a.Add(40.0, 2.0);
  a.Add(40.0, 8.0);
  a.Add(50.0,12.0);
  a.Add(50.0,18.0);

  const int max_x = 78;
  const int max_y = 20;
  ribi::DrawCanvas c(
    max_x,
    max_y,
    ribi::CanvasColorSystem::invert,
    ribi::CanvasCoordinatSystem::graph
  );

  c.DrawLine(0.0,0.0,max_x,0.0);
  c.DrawLine(0.0,0.0,0.0,max_y);

  //Plot values (note: these won't be visible in Canvas)
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (const auto p: a.GetContainer())
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
      catch (ribi::ExceptionNoExtrapolation<MultiApproximator_t::key_type>& e)
      {

      }
    }
  }
  std::cout << c << std::endl;
}

/* Screen output

-
o                                                --
o                                                --
o                            --
o                            oo                  --
o                           -dd-                -o-
o                          -oooo-              -o-
o                         -o-  -o-            -o---
o                        -o-    -o-          -o- --
o                       -o-      -o-        -o-
o                      -o-        -o-      -o-
o                     -o-          -o- -- -o-
o                  ---o-            -o----o-
o                  -oo-              -o--o-
o                  -o-                -oo-
o                  --                  --
o                  --
o                  --                  --
o                                      --
Moooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo-

Press <RETURN> to close this window...

*/
