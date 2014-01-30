//Code adapted from
//http://www.boost.org/doc/libs/1_48_0/libs/timer/doc/cpu_timers.html
#include <cmath>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/timer/timer.hpp>
#pragma GCC diagnostic pop

//Won't build under Windows: need to link to Boost.System
int main()
{
  boost::timer::auto_cpu_timer t;

  for (long i = 0; i < 100000000; ++i)
  {
    std::sqrt(123.456L); // burn some time
  }
}
