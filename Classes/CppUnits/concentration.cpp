#include "concentration.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"

std::istream& boost::units::si::operator>>(std::istream& is, Concentration& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-3");
  is >> unit;
  assert(unit == "mol");
  sd = Concentration(value * boost::units::si::mole / boost::units::si::cubic_meter);
  return is;
}

#ifndef NDEBUG
void ribi::units::TestConcentration() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  using ribi::fileio::FileIo;
  using Concentration = boost::units::quantity<boost::units::si::concentration>;
  //Concentration is in species per square meter
  {
    const Concentration d{
      1.0 * boost::units::si::mole / boost::units::si::cubic_meter
    };
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    std::cerr << t << std::endl;
    assert(t.substr(t.size() - 8, 8) == "m^-3 mol");
  }
  //Concentration uses a dot as a seperator
  {
    const Concentration d{12.34 * boost::units::si::mole / boost::units::si::cubic_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t == "12.34 m^-3 mol");
  }
  //Concentration file I/O, one Concentration
  {
    const Concentration d{12.34 * boost::units::si::mole / boost::units::si::cubic_meter};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    Concentration d_too;
    f >> d_too;
    if (d != d_too)
    {
      std::cerr << d << '\n'
        << d_too << '\n'
      ;
    }
    assert(d == d_too);
  }
  //Concentration file I/O, two Concentration
  {
    const Concentration a{12.34 * boost::units::si::mole / boost::units::si::cubic_meter};
    const Concentration b{23.45 * boost::units::si::mole / boost::units::si::cubic_meter};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    Concentration a_too;
    Concentration b_too;
    f >> a_too >> b_too;
    if (a != a_too)
    {
      std::cerr << a << '\n'
        << a_too << '\n'
      ;
    }
    if (b != b_too)
    {
      std::cerr << a << '\n'
        << b_too << '\n'
      ;
    }
    assert(a == a_too);
    assert(b == b_too);
  }
}
#endif
