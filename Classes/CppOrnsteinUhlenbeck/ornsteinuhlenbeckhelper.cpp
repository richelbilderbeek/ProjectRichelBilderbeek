#include "ornsteinuhlenbeckhelper.h"

#include <algorithm>
#include <iostream>
#include <limits>

#include <boost/math/constants/constants.hpp>

#include "brownianmotionprocess.h"
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
  if (cand_mean_reversion_rate == 0.0)
  {
    const double a{
      CalcLogLikelihood(
        v,
        dt,
        -std::numeric_limits<double>::epsilon(),
        cand_target_mean,
        cand_volatility
      )
    };
    const double b{
      CalcLogLikelihood(
        v,
        dt,
        std::numeric_limits<double>::epsilon(),
        cand_target_mean,
        cand_volatility
      )
    };
    return (a+b)/2.0;
  }



  if (dt <= 0.0) return std::numeric_limits<double>::min();
  //Any non-zero cand_mean_reversion_rate is fine
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
  const bool verbose{false};
  using std::begin; using std::end; using std::accumulate;

  const int n{static_cast<int>(v.size())};
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
      << "n: " << n << '\n'
      << "sx: " << sx << '\n'
      << "sy: " << sy << '\n'
      << "sxx: " << sxx << '\n'
      << "sxy: " << sxy << '\n'
      << "syy: " << syy << '\n'
    ;
  }

  assert( ( (n_d * (sxx - sxy)) - ( (sx*sx) - (sx*sy)) ) != 0.0);

  target_mean_hat
    =  ((sy * sxx) - (sx * sxy))
     / ( (n_d * (sxx - sxy)) - ( (sx*sx) - (sx*sy)) )
  ;

  const double nmu2{n_d*target_mean_hat*target_mean_hat};

  const double mean_reversion_rate_hat_numerator{
    sxy - (target_mean_hat*sx) - (target_mean_hat*sy) + nmu2
  };
  const double mean_reversion_rate_hat_denominator{
    sxx - (2.0*target_mean_hat*sx) + nmu2
  };

  if (verbose)
  {
    std::clog
      << "target_mean_hat: " << target_mean_hat << '\n'
      << "nmu2: " << nmu2 << '\n'
      << "mean_reversion_rate_hat_numerator: " << mean_reversion_rate_hat_numerator << '\n'
      << "mean_reversion_rate_hat_denominator: " << mean_reversion_rate_hat_denominator << '\n'
      << "n/d: " << (mean_reversion_rate_hat_numerator/mean_reversion_rate_hat_denominator) << '\n'
    ;
  }
  assert(mean_reversion_rate_hat_denominator != 0.0);
  assert(
        mean_reversion_rate_hat_numerator
      / mean_reversion_rate_hat_denominator
    > 0.0
  );

  mean_reversion_rate_hat
    = -std::log(
        mean_reversion_rate_hat_numerator
      / mean_reversion_rate_hat_denominator
    ) / dt
  ;

  const double alpha{std::exp(-mean_reversion_rate_hat*dt)};

  const double beta_term_1{syy};
  const double beta_term_2{2.0*alpha*sxy};
  const double beta_term_3{alpha*alpha*sxx};
  const double beta_term_4{2.0*target_mean_hat*(1.0-alpha)*(sy - (alpha*sx))};
  const double beta_term_5{nmu2 * (1.0-alpha)*(1.0-alpha)};

  const double beta{
    (
      beta_term_1
      - beta_term_2
      + beta_term_3
      - beta_term_4
      + beta_term_5
    ) / n_d
  };

  if (verbose)
  {
    std::clog
      << "alpha: " << alpha << '\n'
      << "beta_term_1: " << beta_term_1 << '\n'
      << "beta_term_2: " << beta_term_2 << '\n'
      << "beta_term_3: " << beta_term_3 << '\n'
      << "beta_term_4: " << beta_term_4 << '\n'
      << "beta_term_5: " << beta_term_5 << '\n'
      << "beta: " << beta << '\n'
    ;
  }


  volatility_hat
    = std::sqrt(
        (beta * 2.0 * mean_reversion_rate_hat)
      / (1.0-(alpha*alpha))
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
    const double expected_mean_reversion_rate{0.150065};
    const double expected_target_mean{-21.2912};
    const double expected_volatility{10.9281};
    assert(std::abs(ml_mean_reversion_rate - expected_mean_reversion_rate) < 0.001);
    assert(std::abs(ml_target_mean - expected_target_mean) < 0.001);
    assert(std::abs(ml_volatility - expected_volatility) < 0.001);
    //CalcLogLikelihood
    const double max_log_likelihood{
      Helper().CalcLogLikelihood(known_xs,known_dt,ml_mean_reversion_rate,ml_target_mean,ml_volatility)
    };
    const double expected_max_log_likelihood{-78.4367};
    assert(std::abs(max_log_likelihood - expected_max_log_likelihood) < 0.0001);
  }
  ///Incorrectly labeled as bug:
  ///Brownian motion run for RNG seed of 64 results in a MaxLogLikelihood of 0.0
  ///This used to be 2,2250738585072014e-308 (the minimum double value)
  ///but changes to -131.90782856283087 if negative mean_reversion_rates are allowed
  {
    ribi::bm::Parameters parameters(1.0,64);
    ribi::bm::Process sim(parameters);
    const double init_x{0.0};
    double x = init_x;
    std::vector<double> xs = {x};

    for (int i=0; i!=100; ++i)
    {
      x = sim.CalcNext(x);
      xs.push_back(x);
    }

    const double dt{1.0};
    double mean_reversion_rate_hat{0.0};
    double target_mean_hat{0.0};
    double volatility_hat{0.0};
    Helper().CalcMaxLikelihood(xs,dt,mean_reversion_rate_hat,target_mean_hat,volatility_hat);
    const double max_log_likelihood{
      Helper().CalcLogLikelihood(xs,dt,mean_reversion_rate_hat,target_mean_hat,volatility_hat)
    };
    assert(max_log_likelihood != 0.0);
    const double expected_max_log_likelihood{
      -131.906
    };
    assert(std::abs(max_log_likelihood - expected_max_log_likelihood) < 0.001);
  }
  //Allow mean_reversion_rate of zero
  {
    const double log_likelihood_minus{
      Helper().CalcLogLikelihood(
        known_xs,
        known_dt,
        -std::numeric_limits<double>::epsilon(),
        known_target_mean,
        known_volatility
      )
    };
    const double log_likelihood_zero{
      Helper().CalcLogLikelihood(
        known_xs,
        known_dt,
        0.0000,
        known_target_mean,
        known_volatility
      )
    };
    const double log_likelihood_plus{
      Helper().CalcLogLikelihood(
        known_xs,
        known_dt,
        std::numeric_limits<double>::epsilon(),
        known_target_mean,
        known_volatility
      )
    };
    assert(log_likelihood_minus >= log_likelihood_zero);
    assert(log_likelihood_zero >= log_likelihood_plus);

    //Note: resolution too low to distinguish likelihoods
    assert(log_likelihood_minus == log_likelihood_plus);
  }

}
#endif
