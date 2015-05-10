
#include "poisoningfunction.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"

void PoisoningFunction::Test() noexcept
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
  {
    const InvertedExponentialPoisoning f;
  }
  /*
  {
    const InvertExponentialPoisoning f;
    assert(std::abs(f.CalculateSurvivalFraction( 0.0)-1.0) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction( 1.0)-1.0) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(23.0)-0.5) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(35.0)-0.1) < 0.1);
    assert(std::abs(f.CalculateSurvivalFraction(50.0)-0.0) < 0.1);
  }
  */
  //File I/O
  {
    const double r{12.34};
    InvertedExponentialPoisoning c(r);
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<PoisoningFunction> d;
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

double InvertedExponentialPoisoning::CalculateSurvivalFraction(
  const ribi::units::Concentration sulfide_concentration
) const
{
  if (sulfide_concentration < 0.0 * boost::units::si::mole / boost::units::si::cubic_meter)
  {
    std::stringstream s;
    s << "InvertedExponentialPoisoning::CalculateSurvivalFraction: "
      << "sulfide_concentration must be positive, "
      << "value supplied was " << sulfide_concentration
    ;
    throw std::logic_error(s.str());
  }
  if (std::isnan(sulfide_concentration.value()))
  {
    std::stringstream s;
    s << "InvertedExponentialPoisoning::CalculateSurvivalFraction: "
      << "sulfide_concentration must be a number, "
      << "value supplied was " << sulfide_concentration.value()
    ;
    throw std::logic_error(s.str());
  }
  assert(sulfide_concentration >= 0.0 * boost::units::si::mole / boost::units::si::cubic_meter);
  const double s{sulfide_concentration.value()};
  assert(s >= 0.0);
  const double p_survive{
    m_max * (1.0 - std::exp(-m_r * s))
  };
  return p_survive;
}

std::string InvertedExponentialPoisoning::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "InvertedExponentialPoisoning" << " "
    << m_r << " "
    << m_max
  ;
  return s.str();
}

std::ostream& operator<<(std::ostream& os, const PoisoningFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& operator>>(std::istream& is, std::shared_ptr<PoisoningFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "InvertedExponentialPoisoning");
  double r{0.0};
  is >> r;
  double max{0.0};
  is >> max;
  f = std::make_shared<InvertedExponentialPoisoning>(r,max);
  return is;
}
