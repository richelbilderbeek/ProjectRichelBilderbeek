#ifndef POISONINGFUNCTION_H
#define POISONINGFUNCTION_H

#include <string>
#include <memory>

#include "concentration.h"

///A strategy
struct PoisoningFunction
{
  PoisoningFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }
  virtual ~PoisoningFunction() {}
  ///The fraction that will survive
  ///Will throw if seagrass_density is less than zero
  virtual double CalculateSurvivalFraction(const ribi::units::Concentration sulfide_concentration) const = 0;

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
struct InvertedExponentialPoisoning : public PoisoningFunction
{
  InvertedExponentialPoisoning(
    const double r = 0.2,
    const double max = 0.009
  )
    : m_r{r}, m_max{max} {}
  ~InvertedExponentialPoisoning() {}
  ///The fraction that will survive
  ///Will throw if seagrass_density is less than zero
  double CalculateSurvivalFraction(const ribi::units::Concentration sulfide_concentration) const override;
  std::string ToStr() const noexcept override;
  const double m_r;
  const double m_max;
};

std::ostream& operator<<(std::ostream& os, const PoisoningFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<PoisoningFunction>& f) noexcept;


#endif // POISONINGFUNCTION_H
