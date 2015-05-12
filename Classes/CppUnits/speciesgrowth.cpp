#ifndef NDEBUG
#include "speciesgrowth.h"

#include <boost/units/io.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "fileio.h"
#include "testtimer.h"
#include "speciesdensity.h"
#include "rate.h"

std::istream& boost::units::si::operator>>(std::istream& is, SpeciesGrowth& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-2");
  is >> unit;
  assert(unit == "s^-1");
  sd = SpeciesGrowth(
    value
    * boost::units::si::species_per_square_meter_per_second);
  return is;
}

void ribi::units::TestSpeciesGrowth() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    TestSpeciesDensity();
    TestRate();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  using ribi::fileio::FileIo;
  using SpeciesGrowth = boost::units::quantity<boost::units::si::species_growth>;
  //Species density is in species per square meter
  {
    const SpeciesGrowth d{
      1.0 * boost::units::si::species_per_square_meter_per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    //std::cerr << t << std::endl;
    assert(t.substr(t.size() - 9, 9) == "m^-2 s^-1");
  }
  //Species density uses a dot as a seperator
  {
    const SpeciesGrowth d{12.34 * boost::units::si::species_per_square_meter_per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    assert(t == "12.34 m^-2 s^-1");
  }
  //Species growth can be multiplied by an area to obtain the growth rate
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const SpeciesGrowth d{0.1 * boost::units::si::species_per_square_meter_per_second};
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    assert(t.substr(t.size() - 4, 4) == "s^-1");
  }
  //Species density file I/O, one SpeciesGrowth
  {
    const SpeciesGrowth d{12.34 * boost::units::si::species_per_square_meter_per_second};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    SpeciesGrowth d_too;
    f >> d_too;
    if (d != d_too)
    {
      std::cerr << d << '\n'
        << d_too << '\n'
      ;
    }
    assert(d == d_too);
  }
  //Species density file I/O, two SpeciesGrowth
  {
    const SpeciesGrowth a{12.34 * boost::units::si::species_per_square_meter_per_second};
    const SpeciesGrowth b{23.45 * boost::units::si::species_per_square_meter_per_second};
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    SpeciesGrowth a_too;
    SpeciesGrowth b_too;
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
  //Combining SpeciesDensity, SpeciesGrowth and Rate
  //Exponential growth
  {
    const double n_unitless{0.7};
    const double r_unitless{1.3};
    const SpeciesDensity n{n_unitless * boost::units::si::species_per_square_meter};
    const Rate r{r_unitless * boost::units::si::per_second};
    const SpeciesGrowth dndt{n * r};
    assert(dndt.value() == n_unitless * r_unitless);
  }
  //Logistic growth
  {
    const double n_unitless{0.7};
    const double k_unitless{2.0};
    const double r_unitless{1.3};
    const SpeciesDensity n{n_unitless * boost::units::si::species_per_square_meter};
    const SpeciesDensity k{k_unitless * boost::units::si::species_per_square_meter};
    const Rate r{r_unitless * boost::units::si::per_second};
    const SpeciesGrowth dndt{ n * r * (1.0 - (n / k))};
    assert(dndt.value() == n_unitless * r_unitless * (1.0 - (n_unitless / k_unitless)));
  }
}
#endif
