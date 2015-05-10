#include "loripesconsumptionfunction.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "fileio.h"
#include "testtimer.h"

void LoripesConsumptionFunction::Test() noexcept
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
  using boost::units::si::species_per_square_meters;

  //Shape of function
  {
    const InvertedExponentialConsumption p;
    assert(std::abs(p.CalculateConsumptionRate(  0.0 * species_per_square_meters)-0.0) < 0.1);
    assert(std::abs(p.CalculateConsumptionRate( 20.0 * species_per_square_meters)-0.6) < 0.1);
    assert(std::abs(p.CalculateConsumptionRate( 60.0 * species_per_square_meters)-0.9) < 0.1);
    assert(std::abs(p.CalculateConsumptionRate(100.0 * species_per_square_meters)-1.0) < 0.1);
  }
  //File I/O
  {
    const double r{12.34};
    InvertedExponentialConsumption c(r);
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<LoripesConsumptionFunction> d;
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

InvertedExponentialConsumption::InvertedExponentialConsumption(
  const double r)
  : m_r{r}
{
  assert(m_r >= 0.0);
}


double InvertedExponentialConsumption::CalculateConsumptionRate(
  const ribi::units::SpeciesDensity seagrass_density
) const noexcept
{
  assert(seagrass_density >= 0.0 * boost::units::si::species_per_square_meters);
  const double n{seagrass_density.value()};
  assert(n >= 0.0);
  const double result{
    1.0 - std::exp(-m_r * n)
  };
  /*
  if (result < 0.0)
  {
    return 0.0;
  }
  */
  assert(result >= 0.0);
  assert(result <= 1.0);
  return result;
}

std::string InvertedExponentialConsumption::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "InvertedExponentialConsumption" << " "
    << m_r
  ;
  return s.str();
}

std::ostream& operator<<(std::ostream& os, const LoripesConsumptionFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& operator>>(std::istream& is, std::shared_ptr<LoripesConsumptionFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "InvertedExponentialConsumption");
  double r{0.0};
  is >> r;
  f = std::make_shared<InvertedExponentialConsumption>(r);
  return is;
}
