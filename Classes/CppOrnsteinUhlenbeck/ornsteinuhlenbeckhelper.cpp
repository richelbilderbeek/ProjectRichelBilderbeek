#include "ornsteinuhlenbeckhelper.h"

#include <algorithm>
#include <iostream>
#include <limits>

#include <boost/math/constants/constants.hpp>

#include "testtimer.h"
#include "trace.h"

ribi::ou::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::ou::Helper::CalcLogLikelihood(
  const std::vector<double>& v,
  const double dt,
  const double cand_mean_reversion_rate,
  const double cand_target_mean,
  const double cand_volatility
) const
{
  if (dt <= 0.0) return std::numeric_limits<double>::min();
  if (cand_mean_reversion_rate <= 0.0) return std::numeric_limits<double>::min();
  if (v.size() < 2) return std::numeric_limits<double>::min();
  const double n{static_cast<double>(v.size())};

  const double sum{
    std::inner_product(
      std::begin(v) + 1,std::end(v),
      std::begin(v),
      0.0,
      std::plus<double>(), //Sum the results
      [dt,cand_mean_reversion_rate,cand_target_mean](const double a, const double b) //a: s_i, b: s_i-1
      {
        const double x {
          a
          - (b * std::exp(-cand_mean_reversion_rate * dt))
          - (cand_target_mean * (1.0 - std::exp(-cand_mean_reversion_rate*dt))),
        };
        return x*x;
      }
    )
  };
  const double sigma_hat2{
    cand_volatility * cand_volatility * (1.0 - std::exp(-2.0 * cand_mean_reversion_rate * dt))
    / (2.0 * cand_mean_reversion_rate)
  };
  const double sigma_hat{std::sqrt(sigma_hat2)};


  const double log_likelihood{
    ((-n/2.0) * std::log(boost::math::constants::two_pi<double>()))
    - (n * std::log(sigma_hat))
    - (sum / (2.0 * sigma_hat2))
  };
  return log_likelihood;
}


void ribi::ou::Helper::CalcMaxLikelihood(
  const std::vector<double>& v,
  const double dt,
  double& mean_reversion_rate_hat,
  double& target_mean_hat,
  double& volatility_hat
) const
{
  using std::begin; using std::end; using std::accumulate;
  const bool verbose{false};

  const int n{static_cast<int>(v.size() - 1)};
  const double n_d{static_cast<double>(n)};
  const double sx{std::accumulate(begin(v),end(v)-1,0.0)};
  const double sy{std::accumulate(begin(v)+1,end(v),0.0)};
  const double sxx{
    std::accumulate(
      begin(v),end(v)-1,
      0.0,
      [](const double init, const double x) { return init + (x*x); }
    )
  };
  const double sxy{
    std::inner_product(
      begin(v),end(v)-1,
      begin(v) + 1,
      0.0
    )
  };
  const double syy{
    std::accumulate(
      begin(v)+1,end(v),0.0,
      [](const double init, const double x) { return init + (x*x); }
    )
  };

  if (verbose)
  {
    std::clog
      << "sx: " << sx << '\n'
      << "sy: " << sy << '\n'
      << "sxx: " << sxx << '\n'
      << "sxy: " << sxy << '\n'
      << "syy: " << syy << '\n'
    ;
  }

  target_mean_hat
    =  ((sy * sxx) - (sx * sxy))
     / ( (n_d * (sxx - sxy)) - ( (sx*sx) - (sx*sy)) )
  ;

  const double nmu2{n_d*target_mean_hat*target_mean_hat};

  mean_reversion_rate_hat
    = -std::log(
        (sxy - (target_mean_hat*sx) - (target_mean_hat*sy) + nmu2 )
      / (sxx - (2.0*target_mean_hat*sx) + nmu2)
    ) / dt
  ;


  const double a{std::exp(-mean_reversion_rate_hat*dt)};
  const double sigmah2{
    (
      syy
      - (2.0*a*sxy)
      + (a*a*sxx)
      - (2.0*target_mean_hat*(1.0-a)*(sy - (a*sx)))
      + (nmu2 * (1.0-a)*(1.0-a))
    ) / n_d
  };

  volatility_hat
    = std::sqrt(
        (sigmah2 * 2.0 * mean_reversion_rate_hat)
      / (1.0-(a*a))
    )
  ;
}





#ifndef NDEBUG
void ribi::ou::Helper::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ///Testing dataset
  //Run a Ornsein-Uhlenbeck motion process for dt = 1.0
  const std::vector<double> known_noises
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

  const std::vector<double> known_xs
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
  const double known_mean_reversion_rate{0.1};
  const double known_target_mean{0.0};
  const double known_volatility{10.0};
  //const double known_init_x{0.0};
  const double known_dt{1.0};

  //CalcLogLikelihood of the known parameters
  {
    const double log_likelihood{
      Helper().CalcLogLikelihood(
        known_xs,
        known_dt,
        known_mean_reversion_rate,
        known_target_mean,
        known_volatility
      )
    };
    const double expected_log_likelihood{-79.422965153555438};
    assert(std::abs(log_likelihood - expected_log_likelihood) < 0.000001);
  }

  //CalcMaxLikelihood
  {
    double ml_mean_reversion_rate{0.0};
    double ml_target_mean{0.0};
    double ml_volatility{0.0};
    Helper().CalcMaxLikelihood(known_xs,known_dt,ml_mean_reversion_rate,ml_target_mean,ml_volatility);
    const double expected_mean_reversion_rate{0.155819};
    const double expected_target_mean{-21.8686};
    const double expected_volatility{11.2043};
    if (1 == 1)
    {
      std::cout << "Found    - Expected" << '\n'
        << ml_mean_reversion_rate << " " << expected_mean_reversion_rate << '\n'
        << ml_target_mean << " " << expected_target_mean << '\n'
        << ml_volatility << " " << expected_volatility << '\n'
      ;
    }
    assert(std::abs(ml_mean_reversion_rate - expected_mean_reversion_rate) < 0.001);
    assert(std::abs(ml_target_mean - expected_target_mean) < 0.001);
    assert(std::abs(ml_volatility - expected_volatility) < 0.001);
    //CalcLogLikelihood

    const double max_log_likelihood{
      Helper().CalcLogLikelihood(known_xs,known_dt,ml_mean_reversion_rate,ml_target_mean,ml_volatility)
    };
    const double expected_max_log_likelihood{-78.446232738006074};
    assert(std::abs(max_log_likelihood - expected_max_log_likelihood) < 0.000000001);
  }
}
#endif
