#include "seagrassgrowthfunction.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "testtimer.h"
#include "speciesdensity.h"
#include "speciesgrowth.h"

SeagrassGrowthFunction::SeagrassGrowthFunction()
{
  #ifndef NDEBUG
  Test();
  #endif
}


void SeagrassGrowthFunction::Test() noexcept
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
    const SeagrassLogisticGrowth f(
      1.0 * species_per_square_meter,
      1.1 * per_second
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
    const SeagrassLogisticGrowth c(
      k * species_per_square_meter,
      r * per_second
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

SeagrassLogisticGrowth::SeagrassLogisticGrowth(
    const Density carrying_capacity,
    const Rate growth_rate
  )
  : m_carrying_capacity{carrying_capacity},
    m_growth_rate{growth_rate}
{
  using boost::units::si::species_per_square_meter;

  if (m_carrying_capacity < 0.0 * species_per_square_meter)
  {
    std::stringstream s;
    s << "SeagrassLogisticGrowth::SeagrassLogisticGrowth: "
      << "carrying capacity must be positive, "
      << "value supplied was " << m_carrying_capacity
    ;
    throw std::logic_error(s.str());
  }
}

SeagrassLogisticGrowth::Growth
  SeagrassLogisticGrowth::CalculateGrowth(
    const Density seagrass_density
  ) const
{
  using boost::units::si::species_per_square_meter;
  if (seagrass_density < 0.0 * species_per_square_meter)
  {
    std::stringstream s;
    s << "SeagrassLogisticGrowth::CalculateGrowth: "
      << "seagrass_density must be positive, "
      << "value supplied was " << seagrass_density
    ;
    throw std::logic_error(s.str());
  }
  if (std::isnan(seagrass_density.value()))
  {
    std::stringstream s;
    s << "SeagrassLogisticGrowth::CalculateGrowth: "
      << "seagrass_density must be a number, "
      << "value supplied was " << seagrass_density.value()
    ;
    throw std::logic_error(s.str());
  }
  assert(seagrass_density >= 0.0 * boost::units::si::species_per_square_meters);
  const auto r = m_growth_rate;
  const auto k = m_carrying_capacity;
  const auto n = seagrass_density;
  const auto result = r * n * (1.0 - (n/k));
  return result;
}

std::string SeagrassLogisticGrowth::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "SeagrassLogisticGrowth" << " "
    << m_carrying_capacity << " "
    << m_growth_rate
  ;
  return s.str();
}

std::ostream& operator<<(std::ostream& os, const SeagrassGrowthFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& operator>>(std::istream& is, std::shared_ptr<SeagrassGrowthFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "SeagrassLogisticGrowth");
  SeagrassGrowthFunction::Density carrying_capacity;
  is >> carrying_capacity;
  SeagrassGrowthFunction::Rate growth_rate;
  is >> growth_rate;

  f = std::make_shared<SeagrassLogisticGrowth>(carrying_capacity,growth_rate);
  return is;
}
