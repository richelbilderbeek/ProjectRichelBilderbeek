#include "mutualismbreakdownerseagrasscolonisationfunction.h"

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

ribi::mb::SeagrassColonisationFunction::SeagrassColonisationFunction()
{
  #ifndef NDEBUG
  Test();
  #endif
}


#ifndef NDEBUG
void ribi::mb::SeagrassColonisationFunction::Test() noexcept
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
  //using boost::units::si::species_per_square_meter_per_second;
  using boost::units::si::per_second;
  using ribi::units::SpeciesDensity;
  using ribi::units::SpeciesGrowth;
  //Shape of function
  {
    const SeagrassInvertedExponential f(
      0.1,
      1.0 * per_second
    );
    const SpeciesDensity n{
      0.1 * species_per_square_meter
    };
    const SpeciesGrowth dndt{
      f.CalculateColonisation( {n,n})
    };
    assert(dndt.value() > 0.0);
  }
  //File I/O
  {
    const double r{12.34};
    const double a{23.45};
    const SeagrassInvertedExponential c(
      a,
      r * per_second
    );
    const std::string filename{FileIo().GetTempFileName(".txt")};
    {
      std::ofstream f(filename);
      f << c;
    }
    std::ifstream f(filename);
    std::shared_ptr<SeagrassColonisationFunction> d;
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

ribi::mb::SeagrassInvertedExponential::SeagrassInvertedExponential(
    const double alpha,
    const Rate growth_rate
  )
  : m_alpha{alpha},
    m_growth_rate{growth_rate}
{

}

ribi::mb::SeagrassInvertedExponential::Growth
  ribi::mb::SeagrassInvertedExponential::CalculateColonisation(
    const std::vector<Density>& neighbours_seagrass_densities
    //const std::initializer_list<Density>& neighbours_seagrass_densities
  ) const
{
  using boost::units::si::species_per_square_meter;

  const auto n_neighbour
    = std::accumulate(
    std::begin(neighbours_seagrass_densities),
    std::end(neighbours_seagrass_densities),
    0.0 * species_per_square_meter
  );

  const auto r = m_growth_rate;
  const auto a = m_alpha;
  const auto n = n_neighbour;
  const auto result = r * n * (1.0 - std::exp(-a * n.value()));
  return result;
}

std::string ribi::mb::SeagrassInvertedExponential::ToStr() const noexcept
{
  std::stringstream s;
  s
    << "SeagrassInvertedExponential" << " "
    << m_alpha << " "
    << m_growth_rate
  ;
  return s.str();
}

std::ostream& ribi::mb::operator<<(std::ostream& os, const SeagrassColonisationFunction& f) noexcept
{
  os << f.ToStr();
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, std::shared_ptr<SeagrassColonisationFunction>& f) noexcept
{
  std::string type_str;
  is >> type_str;
  assert(type_str == "SeagrassInvertedExponential");
  double alpha;
  is >> alpha;
  SeagrassColonisationFunction::Rate growth_rate;
  is >> growth_rate;

  f = std::make_shared<SeagrassInvertedExponential>(alpha,growth_rate);
  return is;
}
