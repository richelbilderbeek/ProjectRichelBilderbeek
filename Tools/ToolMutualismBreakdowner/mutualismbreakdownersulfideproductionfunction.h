#ifndef SULFIDEPRODUCTIONFUNCTION_H
#define SULFIDEPRODUCTIONFUNCTION_H

#include <string>
#include <memory>

#include "concentration.h"
#include "speciesdensity.h"
#include "concentrationchange.h"
#include "rate.h"

namespace ribi {
namespace mb {

///A strategy
struct SulfideProductionFunction
{
  using Concentration = ribi::units::Concentration;
  using Density = ribi::units::SpeciesDensity;
  using Change = ribi::units::ConcentrationChange;
  using Rate = ribi::units::Rate;

  SulfideProductionFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }
  virtual ~SulfideProductionFunction() {}
  ///The fraction that will survive
  ///Will throw if seagrass_density is less than zero
  virtual Change CalculateProduction(
    const Density seagrass_density
  ) const = 0;


  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct LinearSulfideProduction : public SulfideProductionFunction
{
  LinearSulfideProduction(
    const double a = 0.1
  )
    : m_a{a} {}
  ~LinearSulfideProduction() {}

  Change CalculateProduction(
    const Density seagrass_density
  ) const override;
  std::string ToStr() const noexcept override;
  const double m_a;
};

std::ostream& operator<<(std::ostream& os, const SulfideProductionFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<SulfideProductionFunction>& f) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SULFIDEPRODUCTIONFUNCTION_H
