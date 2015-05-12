#ifndef SEAGRASSGROWTHFUNCTION_H
#define SEAGRASSGROWTHFUNCTION_H

#include <memory>
#include "rate.h"
#include "speciesdensity.h"
#include "speciesgrowth.h"

struct SeagrassGrowthFunction
{
  using Rate = ribi::units::Rate;
  using Density = ribi::units::SpeciesDensity;
  using Growth = ribi::units::SpeciesGrowth;

  SeagrassGrowthFunction();
  virtual ~SeagrassGrowthFunction() {}
  virtual ribi::units::SpeciesGrowth CalculateGrowth(
    const ribi::units::SpeciesDensity seagrass_density
  ) const = 0;
  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct SeagrassLogisticGrowth : public SeagrassGrowthFunction
{
  using Rate = ribi::units::Rate;
  using Density = ribi::units::SpeciesDensity;
  using Growth = ribi::units::SpeciesGrowth;

  SeagrassLogisticGrowth(
    const Density carrying_capacity = 0.0 * boost::units::si::species_per_square_meter,
    const Rate growth_rate = 0.0 * boost::units::si::per_second
  );
  Growth CalculateGrowth(
    const Density seagrass_density
  ) const override;
  std::string ToStr() const noexcept override;
  private:

  const Density m_carrying_capacity;
  const Rate m_growth_rate;
};

std::ostream& operator<<(std::ostream& os, const SeagrassGrowthFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<SeagrassGrowthFunction>& f) noexcept;


#endif // SEAGRASSGROWTHFUNCTION_H
