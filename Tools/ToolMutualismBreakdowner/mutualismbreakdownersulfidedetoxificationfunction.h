#ifndef SULFIDEDETOXIFICATIONFUNCTION_H
#define SULFIDEDETOXIFICATIONFUNCTION_H

#include <string>
#include <memory>

#include "concentration.h"
#include "speciesdensity.h"
#include "concentrationchange.h"
#include "rate.h"

namespace ribi {
namespace mb {

///A strategy
struct SulfideDetoxificationFunction
{
  using Concentration = ribi::units::Concentration;
  using Density = ribi::units::SpeciesDensity;
  using Change = ribi::units::ConcentrationChange;
  using Rate = ribi::units::Rate;

  SulfideDetoxificationFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }
  virtual ~SulfideDetoxificationFunction() {}

  virtual Change CalculateDetoxification(
    const Density seagrass_density,
    const Concentration sulfide_concentration
  ) const = 0;


  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct LinearSulfideDetoxification : public SulfideDetoxificationFunction
{
  LinearSulfideDetoxification(
    const double a = 0.1
  )
    : m_a{a} {}
  ~LinearSulfideDetoxification() {}

  Change CalculateDetoxification(
    const Density seagrass_density,
    const Concentration sulfide_concentration
  ) const override;
  std::string ToStr() const noexcept override;
  const double m_a;
};

std::ostream& operator<<(std::ostream& os, const SulfideDetoxificationFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<SulfideDetoxificationFunction>& f) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SULFIDEDETOXIFICATIONFUNCTION_H
