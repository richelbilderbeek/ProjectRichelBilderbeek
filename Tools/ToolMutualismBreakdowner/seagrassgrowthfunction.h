#ifndef SEAGRASSGROWTHFUNCTION_H
#define SEAGRASSGROWTHFUNCTION_H

#include "speciesdensity.h"
#include "speciesgrowth.h"
/*

struct SeagrassGrowthFunction
{
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
  SeagrassLogisticGrowth(
    const double r,
    const ribi::units::SpeciesDensity k
  );
  ribi::units::SpeciesGrowth CalculateGrowth(
    const ribi::units::SpeciesDensity seagrass_density
  ) const override;
  std::string ToStr() const noexcept override;
  private:

  const ribi::units::SpeciesDensity m_carrying_capacity;
  const double m_growth_rate;


};
*/

#endif // SEAGRASSGROWTHFUNCTION_H
