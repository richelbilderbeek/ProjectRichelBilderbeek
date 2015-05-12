#include "sulfideconsumptionfunction.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"

#ifndef NDEBUG
void SulfideConsumptionFunction::Test() noexcept
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
  //using boost::units::si::species_per_square_meters;
  //using boost::units::si::species_per_square_meter;

  //Shape of function
  {
    const LinearConsumption p;
    /*
    assert(std::abs(p.CalculateConsumption(  0.0 * species_per_square_meters)-0.0) < 0.1);
    assert(std::abs(p.CalculateConsumption( 20.0 * species_per_square_meters)-0.6) < 0.1);
    assert(std::abs(p.CalculateConsumption( 60.0 * species_per_square_meters)-0.9) < 0.1);
    assert(std::abs(p.CalculateConsumption(100.0 * species_per_square_meters)-1.0) < 0.1);
    */
  }
  //File I/O
  {
    const double r{12.34};
    LinearConsumption c(r);
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<SulfideConsumptionFunction> d;
    f >> d;
    assert(d);
    if (c.ToStr() != d->ToStr())
    {
      std::cerr
        << c.ToStr() << '\n'
        << d->ToStr() << '\n'
      ;
    }
    assert(c.ToStr() == d->ToStr());
    FileIo().DeleteFile(filename);
  }
}
#endif // NDEBUG


LinearConsumption::Change LinearConsumption::CalculateConsumption(
  const Concentration sulfide_concentration,
  const Density loripes_density
) const
{
  using boost::units::si::species_per_square_meter;
  using boost::units::si::second;
  const auto l = loripes_density;
  const auto s = sulfide_concentration;
  const auto dsdt = l * s * m_a / species_per_square_meter / second;
  return dsdt;
}

std::string LinearConsumption::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "LinearConsumption" << " "
    << m_a
  ;
  return s.str();
}

std::ostream& operator<<(std::ostream& os, const SulfideConsumptionFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& operator>>(std::istream& is, std::shared_ptr<SulfideConsumptionFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "LinearConsumption");
  double a{0.0};
  is >> a;
  f = std::make_shared<LinearConsumption>(a);
  return is;
}
