#ifndef BROWNIANMOTIONHELPER_H
#define BROWNIANMOTIONHELPER_H

#include <vector>

namespace ribi {
namespace bm {

///Performs a Brownian motion
struct Helper
{
  Helper();

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  double CalcLogLikelihood(
    const std::vector<double>& v,
    const double cand_volatility
  ) const;

  ///Calculate the parameters that have a maximum likelihood in generating the values v
  void CalcMaxLikelihood(
    const std::vector<double>& v,
    double& volatility_hat
  ) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace bm
} //~namespace ribi

#endif // BROWNIANMOTIONHELPER_H
