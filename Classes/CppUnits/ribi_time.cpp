#include "ribi_time.h"

#include <fstream>
#include <sstream>

#include <boost/units/io.hpp>

#include "fileio.h"

std::istream& boost::units::si::operator>>(std::istream& is, Time& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "s");
  sd = Time(value * seconds);
  return is;
}

#ifndef NDEBUG
#include "testtimer.h"

#include <iostream>

void ribi::units::TestTime() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  using ribi::fileio::FileIo;
  using Time = boost::units::quantity<boost::units::si::time>;
  using boost::units::si::seconds;

  //Time is in seconds
  {
    const Time d{1.0 * seconds};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 1,1) == "s");
  }
  //Time uses a dot as a seperator
  {
    const Time d{12.34 * seconds};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t == "12.34 s");
  }
  //Time file I/O, one Time
  {
    const Time d{12.34 * seconds};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    Time d_too;
    f >> d_too;
    if (d != d_too)
    {
      std::cerr << d << '\n'
        << d_too << '\n'
      ;
    }
    assert(d == d_too);
  }
  //Time file I/O, two Time
  {
    const Time a{12.34 * seconds};
    const Time b{23.45 * seconds};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    Time a_too;
    Time b_too;
    f >> a_too >> b_too;
    if (a != a_too)
    {
      std::cerr << a << '\n'
        << a_too << '\n'
      ;
    }
    assert(a == a_too);
    if (b != b_too)
    {
      std::cerr << b << '\n'
        << b_too << '\n'
      ;
    }
    assert(b == b_too);
  }
}
#endif
