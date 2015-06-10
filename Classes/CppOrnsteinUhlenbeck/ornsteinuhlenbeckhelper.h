#ifndef ORNSTEINUHLENBECKHELPER_H
#define ORNSTEINUHLENBECKHELPER_H

#include "ribi_time.h"
#include "rate.h"
#include <vector>

namespace ribi {
namespace ou {

struct Helper
{
  using Time = ribi::units::Time;
  using Rate = ribi::units::Rate;

  Helper();

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  ///Even allows negative mean_reversion_rate
  double CalcLogLikelihood(
    const std::vector<double>& v,
    const Time dt,
    const Rate cand_mean_reversion_rate,
    const double cand_target_mean,
    const Rate cand_volatility
  ) const;

  ///Calculate the parameters that have a maximum likelihood in generating the values v
  void CalcMaxLikelihood(
    const std::vector<double>& v,
    const Time dt,
    Rate& mean_reversion_rate_hat,
    double& target_mean_hat,
    Rate& volatility_hat
  ) const;

  double CalcMaxLogLikelihood(const std::vector<double>& v) const;


  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ou
} //~namespace ribi

#endif // ORNSTEINUHLENBECKHELPER_H
