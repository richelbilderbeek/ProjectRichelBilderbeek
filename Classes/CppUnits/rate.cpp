#include "rate.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/units/io.hpp>

#include "speciesdensity.h"

std::istream& boost::units::si::operator>>(std::istream& is, Rate& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "s^-1");
  sd = Rate(
    value
    * boost::units::si::per_second);
  return is;
}

#ifndef NDEBUG
#include "fileio.h"
#include "testtimer.h"
void ribi::units::TestRate() noexcept
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
  using Rate = boost::units::quantity<boost::units::si::rate>;
  //Species density is in species per square meter
  {
    const Rate d{
      1.0 * boost::units::si::per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    //std::cerr << t << std::endl;
    assert(t.substr(t.size() - 4, 4) == "s^-1");
  }
  //Species density uses a dot as a seperator
  {
    const Rate d{12.34 * boost::units::si::per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t == "12.34 s^-1");
  }
  //Species growth can be multiplied by an area to obtain the growth rate
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const Rate d{0.1 * boost::units::si::per_second};
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 4, 4) == "s^-1");
  }
  //Species density file I/O, one Rate
  {
    const Rate d{12.34 * boost::units::si::per_second};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    Rate d_too;
    f >> d_too;
    if (d != d_too)
    {
      std::cerr << d << '\n'
        << d_too << '\n'
      ;
    }
    assert(d == d_too);
  }
  //Species density file I/O, two Rate
  {
    const Rate a{12.34 * boost::units::si::per_second};
    const Rate b{23.45 * boost::units::si::per_second};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    Rate a_too;
    Rate b_too;
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
