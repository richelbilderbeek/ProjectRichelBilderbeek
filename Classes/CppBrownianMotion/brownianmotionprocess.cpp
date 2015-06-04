#include "brownianmotionprocess.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "brownianmotionhelper.h"
#include <boost/math/constants/constants.hpp>

#include "testtimer.h"

ribi::bm::Process::Process(
  const Parameters& parameters
)
  : m_normal_distribution(0.0,1.0),
    m_parameters{parameters},
    m_rng(parameters.GetRngSeed())
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::bm::Process::CalcNext(const double x)
{
  const double random_normal{m_normal_distribution(m_rng)};
  return CalcNext(x,random_normal);
}

double ribi::bm::Process::CalcNext(
  const double x,
  const double random_normal
) const
{
  const double dt{1.0};
  const double volatility{m_parameters.GetVolatility()};
  const double dx{
    random_normal * volatility
  };
  return x + (dt * dx);
}

#ifndef NDEBUG
void ribi::bm::Process::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Helper();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Create a Brownian motion with volatility
  {
    const double volatility{1.0};
    bm::Process b(volatility);
    double x{0.0};
    std::vector<double> v = {x};
    for (int i=0; i!=100; ++i)
    {
      x = b.CalcNext(x);
      v.push_back(x);
    }
    //Are the likelihoods best at the true volatility?
    const double good_likelihood{Helper().CalcLogLikelihood(v,volatility)};
    const double bad_likelihood{Helper().CalcLogLikelihood(v,volatility * 0.5)};
    const double worse_likelihood{Helper().CalcLogLikelihood(v,volatility * 1.5)};
    assert(good_likelihood > worse_likelihood);
    assert(good_likelihood > bad_likelihood);
    //Is the max likelihood truly the max likelihood?
    double volatility_hat{0.0};
    Helper().CalcMaxLikelihood(v,volatility_hat);
    const double max_likelihood{Helper().CalcLogLikelihood(v,volatility_hat)};
    assert(max_likelihood > good_likelihood);
  }


  //Run a Brownian motion process
  {
    const std::vector<double> noises
      = {
       -1.0268,
       -0.4985,
        0.3825,
       -0.8102,
       -0.1206,
       -1.9604,
        0.2079,
        0.9134,
        2.1375,
        0.5461,
        1.4335,
        0.4414,
       -2.2912,
        0.3249,
       -1.3019,
       -0.8995,
        0.0281,
       -1.0959,
       -0.8118,
       -1.3890
      };
    const std::vector<double> xs_expected
     = {
          0.0,
        -10.268,
        -15.253,
        -11.428,
        -19.53,
        -20.736,
        -40.34,
        -38.261,
        -29.127,
        -7.752,
        -2.291,
        12.044,
        16.458,
        -6.454,
        -3.205,
        -16.224,
        -25.219,
        -24.938,
        -35.897,
        -44.015,
        -57.905
      };
    const double volatility{10.0};
    const double init_x{0.0};

    const ribi::bm::Parameters parameters(volatility);
    ribi::bm::Process sim(parameters);

    double x = init_x;
    std::vector<double> xs = {x};

    for (const double noise: noises)
    {
      x = sim.CalcNext(x,noise);
      xs.push_back(x);
    }
    assert(xs.size() == xs_expected.size());
    const int sz{static_cast<int>(xs.size())};
    for (int i=0; i!=sz; ++i)
    {
      assert(std::abs(xs[i]-xs_expected[i]) < 0.000000001);
    }
  }
}
#endif
