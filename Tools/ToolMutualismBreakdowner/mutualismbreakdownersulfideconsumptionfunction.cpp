#include "mutualismbreakdownersulfideconsumptionfunction.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"

#ifndef NDEBUG
void ribi::mb::SulfideConsumptionFunction::Test() noexcept
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

  //Shape of function
  {
    const LinearConsumption p;
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


ribi::mb::LinearConsumption::Change ribi::mb::LinearConsumption::CalculateConsumption(
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

std::string ribi::mb::LinearConsumption::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "LinearConsumption" << " "
    << m_a
  ;
  return s.str();
}

std::ostream& ribi::mb::operator<<(std::ostream& os, const SulfideConsumptionFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, std::shared_ptr<SulfideConsumptionFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "LinearConsumption");
  double a{0.0};
  is >> a;
  f = std::make_shared<LinearConsumption>(a);
  return is;
}
