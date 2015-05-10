#ifndef NDEBUG
#include "speciesdensity.h"

#include <boost/units/io.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "fileio.h"
#include "testtimer.h"

std::istream& boost::units::si::operator>>(std::istream& is, SpeciesDensity& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-2");
  sd = SpeciesDensity(value * boost::units::si::species_per_square_meter);
  return is;
}

void ribi::units::TestSpeciesDensity() noexcept
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
  using SpeciesDensity = boost::units::quantity<boost::units::si::species_density>;
  //Species density is in species per square meter
  {
    const SpeciesDensity d{1.0 * boost::units::si::species_per_square_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 4, 4) == "m^-2");
  }
  //Species density uses a dot as a seperator
  {
    const SpeciesDensity d{12.34 * boost::units::si::species_per_square_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t == "12.34 m^-2");
  }
  //Species density can be multiplied by an area to obtain the number of species
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const SpeciesDensity d{0.1 * boost::units::si::species_per_square_meter};
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 13, 13) == "dimensionless");
  }
  //Species density file I/O
  {
    const SpeciesDensity d{12.34 * boost::units::si::species_per_square_meter};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    SpeciesDensity d_too;
    f >> d_too;
    if (d != d_too)
    {
      std::cerr << d << '\n'
        << d_too << '\n'
      ;
    }
    assert(d == d_too);
  }
}
#endif
