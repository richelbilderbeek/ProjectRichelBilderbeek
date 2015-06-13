#include "mutualismbreakdownerseagrassgrowthfunction.h"

#include <cassert>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"
#include "speciesdensity.h"
#include "speciesgrowth.h"

ribi::mb::SeagrassGrowthFunction::SeagrassGrowthFunction()
{
  #ifndef NDEBUG
  Test();
  #endif
}


#ifndef NDEBUG
void ribi::mb::SeagrassGrowthFunction::Test() noexcept
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
  using boost::units::si::species_per_square_meter;
  using boost::units::si::per_second;
  using ribi::units::SpeciesDensity;
  using ribi::units::SpeciesGrowth;
  //Shape of function
  {
    const SeagrassStressedLogisticGrowth f(
      1.0 * species_per_square_meter,
      1.1 * per_second,
      0.1 * per_second
    );
    const SpeciesDensity n{
      0.1 * species_per_square_meter
    };
    const SpeciesGrowth dndt{
      f.CalculateGrowth(n)
    };
    assert(dndt.value() > 0.0);
  }
  //File I/O
  {
    const double r{12.34};
    const double k{23.45};
    const double stress{34.56};
    const SeagrassStressedLogisticGrowth c(
      k * species_per_square_meter,
      r * per_second,
      stress * per_second
    );
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<SeagrassGrowthFunction> d;
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

ribi::mb::SeagrassStressedLogisticGrowth::SeagrassStressedLogisticGrowth(
    const Density carrying_capacity,
    const Rate growth_rate,
    const Rate stress_rate
  )
  : m_carrying_capacity{carrying_capacity},
    m_growth_rate{growth_rate},
    m_stress_rate{stress_rate}
{
  using boost::units::si::species_per_square_meter;

  if (m_carrying_capacity <= 0.0 * species_per_square_meter)
  {
    std::stringstream s;
    s << "SeagrassStressedLogisticGrowth::SeagrassStressedLogisticGrowth: "
      << "carrying capacity must be positive, "
      << "value supplied was " << m_carrying_capacity
    ;
    throw std::logic_error(s.str());
  }
}

ribi::mb::SeagrassStressedLogisticGrowth::Growth
  ribi::mb::SeagrassStressedLogisticGrowth::CalculateGrowth(
    const Density seagrass_density
  ) const
{
  using boost::units::si::species_per_square_meter;
  if (seagrass_density < 0.0 * species_per_square_meter)
  {
    std::stringstream s;
    s << "SeagrassStressedLogisticGrowth::CalculateGrowth: "
      << "seagrass_density must be positive, "
      << "value supplied was " << seagrass_density
    ;
    throw std::logic_error(s.str());
  }
  if (std::isnan(seagrass_density.value()))
  {
    std::stringstream s;
    s << "SeagrassStressedLogisticGrowth::CalculateGrowth: "
      << "seagrass_density must be a number, "
      << "value supplied was " << seagrass_density.value()
    ;
    throw std::logic_error(s.str());
  }
  assert(seagrass_density >= 0.0 * boost::units::si::species_per_square_meters);
  const auto r = m_growth_rate;
  const auto k = m_carrying_capacity;
  const auto n = seagrass_density;
  const auto d = m_stress_rate;
  const auto result = n * ((r * (1.0 - (n/k))) - d);
  return result;
}

std::string ribi::mb::SeagrassStressedLogisticGrowth::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "SeagrassStressedLogisticGrowth" << " "
    << m_carrying_capacity << " "
    << m_growth_rate
  ;
  return s.str();
}

std::ostream& ribi::mb::operator<<(std::ostream& os, const SeagrassGrowthFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, std::shared_ptr<SeagrassGrowthFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "SeagrassStressedLogisticGrowth");
  SeagrassGrowthFunction::Density carrying_capacity;
  is >> carrying_capacity;
  SeagrassGrowthFunction::Rate growth_rate;
  is >> growth_rate;

  f = std::make_shared<SeagrassStressedLogisticGrowth>(carrying_capacity,growth_rate);
  return is;
}
