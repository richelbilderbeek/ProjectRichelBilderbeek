#ifndef NDEBUG

#include "massdensity.h"

#include <boost/units/io.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "fileio.h"
#include "testtimer.h"

#ifdef RIBI_USE_MASS_DENSITY
std::istream& boost::units::si::operator>>(std::istream& is, MassDensity& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-2");
  sd = MassDensity(value * boost::units::si::mass_per_square_meter);
  return is;
}
#endif

void ribi::units::TestMassDensity() noexcept
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
  #ifdef RIBI_USE_MASS_DENSITY
  using ribi::fileio::FileIo;
  using MassDensity = boost::units::quantity<boost::units::si::mass_density>;
  //Mass density is in mass per square meter
  {
    const MassDensity d{1.0 * boost::units::si::mass_per_square_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 4, 4) == "m^-2");
  }
  //Mass density uses a dot as a seperator
  {
    const MassDensity d{12.34 * boost::units::si::mass_per_square_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t == "12.34 m^-2");
  }
  //Mass density can be multiplied by an area to obtain the number of mass
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const MassDensity d{0.1 * boost::units::si::mass_per_square_meter};
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 13, 13) == "dimensionless");
  }
  //Mass density file I/O
  {
    const MassDensity d{12.34 * boost::units::si::mass_per_square_meter};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    MassDensity d_too;
    f >> d_too;
    if (d != d_too)
    {
      std::cerr << d << '\n'
        << d_too << '\n'
      ;
    }
    assert(d == d_too);
  }
  #endif // RIBI_USE_MASS_DENSITY
}

#endif
