#ifndef POISONINGFUNCTION_H
#define POISONINGFUNCTION_H

#include <string>
#include <memory>

#include "concentration.h"
#include "speciesdensity.h"
#include "speciesgrowth.h"
#include "rate.h"

namespace ribi {
namespace mb {

///A strategy
struct PoisoningFunction
{
  using Concentration = ribi::units::Concentration;
  using Density = ribi::units::SpeciesDensity;
  using Growth = ribi::units::SpeciesGrowth;
  using Rate = ribi::units::Rate;

  PoisoningFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }
  virtual ~PoisoningFunction() {}
  ///The fraction that will survive
  ///Will throw if seagrass_density is less than zero
  virtual Growth CalculateDecline(
    const Density seagrass_density,
    const Concentration sulfide_concentration
  ) const = 0;


  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

/*

 Survival

 +
 |\
 | \_
 |   \__
 |      ----________
 +--------------------- Sulfide concentration

*/
/*
                 b*e^(a*N)
dN/dt = (1 - ------------- )*m*N*S
             1 + b*e^(a*N)
*/
struct InvertedExponentialPoisoning : public PoisoningFunction
{
  InvertedExponentialPoisoning(
    const double a = 0.1,
    const double b = 0.1,
    const double max = 0.009
  )
    : m_a{a}, m_b{b}, m_max{max} {}
  ~InvertedExponentialPoisoning() {}
  ///The fraction that will survive
  ///Will throw if seagrass_density is less than zero
  Growth CalculateDecline(
    const Density seagrass_density,
    const Concentration sulfide_concentration
  ) const override;
  std::string ToStr() const noexcept override;
  const double m_a;
  const double m_b;
  const double m_max;
};

std::ostream& operator<<(std::ostream& os, const PoisoningFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<PoisoningFunction>& f) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // POISONINGFUNCTION_H
