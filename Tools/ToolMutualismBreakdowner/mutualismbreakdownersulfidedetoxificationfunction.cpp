#include "mutualismbreakdownersulfidedetoxificationfunction.h"

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
void ribi::mb::SulfideDetoxificationFunction::Test() noexcept
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
    const LinearSulfideDetoxification f;
  }
  //File I/O
  {
    const double r{12.34};
    LinearSulfideDetoxification c(r);
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<SulfideDetoxificationFunction> d;
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

ribi::mb::SulfideDetoxificationFunction::Change
  ribi::mb::LinearSulfideDetoxification::CalculateDetoxification(
  const Density seagrass_density,
  const Concentration sulfide_concentration
) const
{
  using boost::units::si::species_per_square_meter;
  using boost::units::si::second;
  const auto detoxification
    = sulfide_concentration * seagrass_density
    * m_a / species_per_square_meter / second
  ;
  return detoxification;
}

std::string ribi::mb::LinearSulfideDetoxification::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "LinearSulfideDetoxification" << " "
    << m_a
  ;
  return s.str();
}

std::ostream& ribi::mb::operator<<(std::ostream& os, const SulfideDetoxificationFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, std::shared_ptr<SulfideDetoxificationFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "LinearSulfideDetoxification");
  double a{0.0};
  is >> a;
  f = std::make_shared<LinearSulfideDetoxification>(a);
  return is;
}
