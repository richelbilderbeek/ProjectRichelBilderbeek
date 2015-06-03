#ifndef BROWNIANMOTIONPROCESS_H
#define BROWNIANMOTIONPROCESS_H

#include "brownianmotionparameters.h"
#include <random>

namespace ribi {
namespace bm {

///Performs a Brownian motion
struct Process
{
  ///volatility: the standard deviation of the noise
  Process(
    const Parameters& parameters
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
  const Parameters m_parameters;
  std::mt19937 m_rng;
};

} //~namespace bm
} //~namespace ribi

#endif // BROWNIANMOTIONPROCESS_H
