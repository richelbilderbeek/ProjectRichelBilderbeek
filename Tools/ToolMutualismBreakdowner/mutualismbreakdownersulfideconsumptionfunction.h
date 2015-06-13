#ifndef LORIPESCONSUMPTIONFUNCTION_H
#define LORIPESCONSUMPTIONFUNCTION_H

#include <iosfwd>
#include <memory>

#include "concentration.h"
#include "concentrationchange.h"
#include "speciesdensity.h"
#include "rate.h"

namespace ribi {
namespace mb {

struct SulfideConsumptionFunction
{
  using Concentration = ribi::units::Concentration;
  using Density = ribi::units::SpeciesDensity;
  using Change = ribi::units::ConcentrationChange;
  using Rate = ribi::units::Rate;

  SulfideConsumptionFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  virtual ~SulfideConsumptionFunction() {}

  virtual Change CalculateConsumption(
    const Concentration sulfide_concentration,
    const Density loripes_density
  ) const = 0;
  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct LinearConsumption : SulfideConsumptionFunction
{
  LinearConsumption(const double a = 0.05)
    : m_a{a} {}
  ~LinearConsumption() {}

  Change CalculateConsumption(
    const Concentration sulfide_concentration,
    const Density loripes_density
  ) const override;
  std::string ToStr() const noexcept override;
  const double m_a;
};

std::ostream& operator<<(std::ostream& os, const SulfideConsumptionFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<SulfideConsumptionFunction>& f) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // LORIPESCONSUMPTIONFUNCTION_H
