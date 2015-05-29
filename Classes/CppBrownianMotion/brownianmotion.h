#ifndef BROWNIANMOTION_H
#define BROWNIANMOTION_H

#include <random>

namespace ribi {

///Performs a Brownian motion
struct BrownianMotion
{
  ///volatility: the standard deviation of the noise
  BrownianMotion(
    const double volatility,
    const int rng_seed = 42
  );

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  static double CalcLogLikelihood(
    const std::vector<double>& v,
    const double cand_volatility
  );

  ///Calculate the parameters that have a maximum likelihood in generating the values v
  static void CalcMaxLikelihood(
    const std::vector<double>& v,
    double& volatility_hat
  );

  ///Calculate the next x. This class will supply the random numbers,
  ///thus these member functions are not const
  double CalcNext(
    const double x
  );

  ///Calculate the next x+dt, supplying the random numbers yourself
  double CalcNext(
    const double x,
    const double random_normal
  ) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:
  std::normal_distribution<double> m_normal_distribution;
  std::mt19937 m_rng;
  const int m_rng_seed;
  const double m_volatility;
};

} //~namespace ribi

#endif // BROWNIANMOTION_H
