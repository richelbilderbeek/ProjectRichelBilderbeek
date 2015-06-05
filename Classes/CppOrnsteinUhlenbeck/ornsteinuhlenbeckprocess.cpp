#include "ornsteinuhlenbeckprocess.h"

#include <cassert>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <boost/math/constants/constants.hpp>

#include "brownianmotionparameters.h"
#include "brownianmotionprocess.h"

#include "ornsteinuhlenbeckhelper.h"
#include "testtimer.h"

ribi::ou::Process::Process(const Parameters& parameters)
  : m_normal_distribution(0.0,1.0),
    m_parameters{parameters},
    m_rng(parameters.GetRngSeed())
{
  #ifndef NDEBUG
  Test();
  #endif
}



double ribi::ou::Process::CalcNext(const double x, const double dt)
{
  try
  {
    const double random_normal{m_normal_distribution(m_rng)};
    return CalcNext(x,dt,random_normal);
  }
  catch (std::logic_error&)
  {
    std::stringstream s;
    s << __func__ << ": delta t must be non-zero and positive, delta t given: " << dt;
    throw std::logic_error(s.str());
  }
}

double ribi::ou::Process::CalcNext(
  const double x,
  const double dt,
  const double random_normal
) const
{
  try
  {
    const double mean_reversion_rate{m_parameters.GetMeanReversionRate()};
    const double target_mean{m_parameters.GetTargetMean()};
    const double volatility{m_parameters.GetVolatility()};

    const double term1{x*std::exp(-mean_reversion_rate*dt)};
    const double term2{target_mean * (1.0-std::exp(-mean_reversion_rate*dt))};
    const double term3{volatility * random_normal * std::sqrt((1.0 - std::exp(-2.0*mean_reversion_rate*dt))  / (2.0 * mean_reversion_rate))};
    const double new_x{
        term1
      + term2
      + term3
    };
    return new_x;
  }
  catch (std::logic_error&)
  {
    std::stringstream s;
    s << __func__ << ": delta t must be non-zero and positive, delta t given: " << dt;
    throw std::logic_error(s.str());
  }
}

#ifndef NDEBUG
void ribi::ou::Process::Test() noexcept
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
  const bool verbose{false};

  //Run Ornstein-Uhlenbeck for dt=0.25 and known results
  {
    ///Many thanks to Thijs van den Berg from sitmo.com
    ///to allow for this detailed test
    const std::vector<double> noises
      = {
        0.0, //Does not matter: this might the noise to generate the initial population?
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
    const std::vector<double> v
      = {
        3.0, //Initial population size
        1.7600,
        1.2693,
        1.1960,
        0.9468,
        0.9532,
        0.6252,
        0.8604,
        1.0984,
        1.4310,
        1.3019,
        1.4005,
        1.2686,
        0.7147,
        0.9237,
        0.7297,
        0.7105,
        0.8683,
        0.7406,
        0.7314,
        0.6232
      };
    assert(v.size() == noises.size());
    const double mean_reversion_rate{3.0};
    const double target_mean{1.0};
    const double volatility{0.5};
    const double dt{0.25};

    ///Many thanks to Thijs van den Berg from sitmo.com
    ///to allow for this detailed test
    double x = 3.0;
    const Parameters parameters(mean_reversion_rate,target_mean,volatility);
    Process p(parameters);
    const int n{static_cast<int>(noises.size())};
    for (int i=1; i!=n; ++i)
    {
      x = p.CalcNext(x,dt,noises[i]);
      assert(std::abs(x - v[i]) < 0.01);
    }
  }

  //Run a Ornsein-Uhlenbeck motion process for dt = 1.0
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
      -9.77536,
      -13.5909,
      -8.65611,
      -15.5457,
      -15.2144,
      -32.43,
      -27.3646,
      -16.0648,
      5.81345,
      10.4592,
      23.1111,
      25.114,
      0.911395,
      3.91778,
      -8.84942,
      -16.5707,
      -14.7263,
      -23.7581,
      -29.2257,
      -39.6681
    };
    const double mean_reversion_rate{0.1};
    const double target_mean{0.0};
    const double volatility{10.0};
    const double init_x{0.0};

    const ribi::ou::Parameters parameters(
      mean_reversion_rate,
      target_mean,
      volatility
    );
    ribi::ou::Process sim(parameters);

    double x = init_x;
    std::vector<double> xs = {x};

    for (const double noise: noises)
    {
      const double dt{1.0};
      x = sim.CalcNext(x,dt,noise);
      xs.push_back(x);
    }
    //std::copy(std::begin(xs),std::end(xs),std::ostream_iterator<double>(std::cout,"\n"));
    assert(xs.size() == xs_expected.size());
    const int sz{static_cast<int>(xs.size())};
    for (int i=0; i!=sz; ++i)
    {
      assert(std::abs(xs[i]-xs_expected[i]) < 0.0001);
    }
  }






  //LogLikelihood on BM with seed 83 gives nan
  {
    const double volatility{0.5};
    const double init_x{0.0};
    const int seed{83};

    const ribi::bm::Parameters parameters(
      volatility,
      seed
    );
    ribi::bm::Process sim(parameters);

    double x = init_x;
    std::vector<double> xs = {x};

    for (int i=0; i!=10; ++i)
    {
      if (verbose) { std::cout << i << ": " << x << '\n'; }
      x = sim.CalcNext(x);
      xs.push_back(x);
    }
    if (verbose) { std::cout << "10: " << x << '\n'; }

    double cand_mean_reversion_rate{0.0};
    double cand_target_mean{0.0};
    double cand_volatility{0.0};
    const double dt{1.0};
    Helper().CalcMaxLikelihood(xs,dt,cand_mean_reversion_rate,cand_target_mean,cand_volatility);
    const double max_log_likelihood{
      Helper().CalcLogLikelihood(xs,dt,cand_mean_reversion_rate,cand_target_mean,cand_volatility)
    };

    if (verbose)
    {
      std::cout << std::setprecision(20)
        << "cand_mean_reversion_rate: " << cand_mean_reversion_rate << '\n'
        << "cand_target_mean: " << cand_target_mean << '\n'
        << "cand_volatility: " << cand_volatility << '\n'
        << "max_log_likelihood: " << max_log_likelihood << '\n'
      ;
    }
    assert(!std::isnan(cand_mean_reversion_rate));
    assert(!std::isnan(cand_volatility));
    assert(!std::isnan(max_log_likelihood));
  }

}
#endif
