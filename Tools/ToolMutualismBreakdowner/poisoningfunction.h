#ifndef POISONINGFUNCTION_H
#define POISONINGFUNCTION_H

#include <string>

#include "speciesdensity.h"

///A strategy
///It returns the fraction of seagrass that will die per sulfide concentration
///The idea is that lone seagrass will die,
///where higher abundances will have a better survival
/*

   |
 1 +---+        <- all will die
   |    \
   |     \
 0 +------+---  <- all will survive

*/
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
  virtual double CalculateSurvivalFraction(const double sulfide_concentration) const = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

///Suggested by Fivash & Martinez
/*

 Survival

 +
 |\
 | \_
 |   \__
 |      ----________
 +--------------------- Sulfide concentration

*/
struct InvertExponentialPoisoning : public PoisoningFunction
{
  InvertExponentialPoisoning(
    const double r = 0.2,
    const double max = 0.009
  )
    : m_r{r}, m_max{max} {}
  ~InvertExponentialPoisoning() {}
  ///The fraction that will survive
  ///Will throw if seagrass_density is less than zero
  double CalculateSurvivalFraction(const double sulfide_concentration) const override;
  std::string ToStr() const noexcept;
  const double m_r;
  const double m_max;
};



#endif // POISONINGFUNCTION_H
