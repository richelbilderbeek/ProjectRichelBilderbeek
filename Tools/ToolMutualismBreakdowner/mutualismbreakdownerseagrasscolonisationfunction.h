#ifndef SEAGRASSCOLONISATIONFUNCTION_H
#define SEAGRASSCOLONISATIONFUNCTION_H

#include <memory>
#include "rate.h"
#include "speciesdensity.h"
#include "speciesgrowth.h"

namespace ribi {
namespace mb {

struct SeagrassColonisationFunction
{
  using Rate = ribi::units::Rate;
  using Density = ribi::units::SpeciesDensity;
  using Growth = ribi::units::SpeciesGrowth;

  SeagrassColonisationFunction();
  virtual ~SeagrassColonisationFunction() {}
  virtual Growth CalculateColonisation(
    const std::vector<Density>& neighbours_seagrass_densities
    //const std::initializer_list<Density>& neighbours_seagrass_densities
  ) const = 0;
  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

// r * N_neighbour * (1 - exp(-alpha * N_neighbour))
struct SeagrassInvertedExponential : public SeagrassColonisationFunction
{
  using Rate = ribi::units::Rate;
  using Density = ribi::units::SpeciesDensity;
  using Growth = ribi::units::SpeciesGrowth;

  SeagrassInvertedExponential(
    const double alpha = 0.1,
    const Rate growth_rate = 1.0 * boost::units::si::per_second
  );

  Growth CalculateColonisation(
    const std::vector<Density>& neighbours_seagrass_densities
    //const std::initializer_list<Density>& neighbours_seagrass_densities
  ) const override;

  const auto& GetAlpha() const noexcept { return m_alpha; }
  const auto& GetGrowthRate() const noexcept { return m_growth_rate; }

  std::string ToStr() const noexcept override;
  private:

  const double m_alpha;
  const Rate m_growth_rate;
};

std::ostream& operator<<(std::ostream& os, const SeagrassColonisationFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<SeagrassColonisationFunction>& f) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SEAGRASSCOLONISATIONFUNCTION_H
