#ifndef ORNSTEINUHLENBECKHELPER_H
#define ORNSTEINUHLENBECKHELPER_H

#include <vector>

namespace ribi {
namespace ou {

struct Helper
{
  Helper();

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  double CalcLogLikelihood(
    const std::vector<double>& v,
    const double dt,
    const double cand_mean_reversion_rate,
    const double cand_target_mean,
    const double cand_volatility
  ) const;

  ///Calculate the parameters that have a maximum likelihood in generating the values v
  void CalcMaxLikelihood(
    const std::vector<double>& v,
    const double dt,
    double& mean_reversion_rate_hat,
    double& target_mean_hat,
    double& volatility_hat
  ) const;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ou
} //~namespace ribi

#endif // ORNSTEINUHLENBECKHELPER_H
