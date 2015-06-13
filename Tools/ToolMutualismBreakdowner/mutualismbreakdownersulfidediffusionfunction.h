#ifndef SULFIDEDIFFUSIONFUNCTION_H
#define SULFIDEDIFFUSIONFUNCTION_H

#include <string>
#include <memory>

#include "concentration.h"
#include "speciesdensity.h"
#include "concentrationchange.h"
#include "rate.h"

namespace ribi {
namespace mb {

///A strategy
struct SulfideDiffusionFunction
{
  using Concentration = ribi::units::Concentration;
  using Density = ribi::units::SpeciesDensity;
  using Change = ribi::units::ConcentrationChange;
  using Rate = ribi::units::Rate;

  SulfideDiffusionFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }
  virtual ~SulfideDiffusionFunction() {}

  virtual Change CalculateDiffusion(
    const Concentration sulfide_concentration
  ) const = 0;


  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct LinearSulfideDiffusion : public SulfideDiffusionFunction
{
  LinearSulfideDiffusion(
    const double a = 0.1
  )
    : m_a{a} {}
  ~LinearSulfideDiffusion() {}

  Change CalculateDiffusion(
    const Concentration sulfide_concentration
  ) const override;
  std::string ToStr() const noexcept override;
  const double m_a;
};

std::ostream& operator<<(std::ostream& os, const SulfideDiffusionFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<SulfideDiffusionFunction>& f) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SULFIDEDIFFUSIONFUNCTION_H
