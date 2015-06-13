#include "mutualismbreakdownersulfideproductionfunction.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"

#ifndef NDEBUG
void ribi::mb::SulfideProductionFunction::Test() noexcept
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
    const LinearSulfideProduction f;
  }
  //File I/O
  {
    const double r{12.34};
    LinearSulfideProduction c(r);
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<SulfideProductionFunction> d;
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

ribi::mb::SulfideProductionFunction::Change
  ribi::mb::LinearSulfideProduction::CalculateProduction(
    const Density seagrass_density
) const
{
  using boost::units::si::mole_per_cubic_meter;
  using boost::units::si::species_per_square_meter;
  using boost::units::si::second;
  const auto production
    = seagrass_density * m_a * mole_per_cubic_meter / species_per_square_meter / second;
  ;
  return production;
}

std::string ribi::mb::LinearSulfideProduction::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "LinearSulfideProduction" << " "
    << m_a
  ;
  return s.str();
}

std::ostream& ribi::mb::operator<<(std::ostream& os, const SulfideProductionFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, std::shared_ptr<SulfideProductionFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "LinearSulfideProduction");
  double a{0.0};
  is >> a;
  f = std::make_shared<LinearSulfideProduction>(a);
  return is;
}
