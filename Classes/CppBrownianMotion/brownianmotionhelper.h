#ifndef BROWNIANMOTIONHELPER_H
#define BROWNIANMOTIONHELPER_H

#include "rate.h"
#include <vector>

namespace ribi {
namespace bm {

///Performs a Brownian motion
struct Helper
{
  using Volatility = ribi::units::Rate;
  using VolatilitySquared = decltype(Volatility() * Volatility());

  Helper();

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  double CalcLogLikelihood(
    const std::vector<double>& v,
    const VolatilitySquared cand_volatility_squared
  ) const;

  ///Calculate the parameters that have a maximum likelihood in generating the values v
  void CalcMaxLikelihood(
    const std::vector<double>& v,
    Volatility& volatility_hat
  ) const;

  double CalcMaxLogLikelihood(const std::vector<double>& v) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace bm
} //~namespace ribi

#endif // BROWNIANMOTIONHELPER_H
