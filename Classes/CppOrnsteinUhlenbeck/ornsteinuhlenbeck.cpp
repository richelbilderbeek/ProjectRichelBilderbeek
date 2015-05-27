#include "ornsteinuhlenbeck.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <boost/math/constants/constants.hpp>

#include "testtimer.h"

ribi::OrnsteinUhlenbeck::OrnsteinUhlenbeck(
  const double mean_reversion_rate,
  const double target_mean,
  const double volatility,
  const int rng_seed
)
  : m_mean_reversion_rate{mean_reversion_rate},
    m_normal_distribution(0.0,1.0),
    m_rng(rng_seed),
    m_rng_seed{rng_seed},
    m_target_mean{target_mean},
    m_volatility{volatility}
{
  #ifndef NDEBUG
  Test();
  #endif
  //TODO: allow zero, then the process falls back to a Brownian process
  if (m_mean_reversion_rate <= 0.0)
  {
    std::stringstream s;
    s << __func__
      << ": mean reversion rate must be positive and non-zero, "
      << "value given is " << m_mean_reversion_rate
    ;
    throw std::logic_error(s.str());
  }

  //TODO: allow zero, then the process falls back to an autoregression
  if (m_volatility <= 0.0)
  {
    std::stringstream s;
    s << __func__
      << ": volatility must be positive and non-zero, "
      << "value given is " << m_volatility
    ;
    throw std::logic_error(s.str());
  }
}

double ribi::OrnsteinUhlenbeck::CalcLogLikelihood(
  const std::vector<double>& v,
  const double dt,
  const double cand_mean_reversion_rate,
  const double cand_target_mean,
  const double cand_volatility
)
{
  assert(dt > 0.0);
  assert(cand_mean_reversion_rate > 0.0);
  assert(v.size() >= 2);
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

void ribi::OrnsteinUhlenbeck::CalcMaxLikelihood(
  const std::vector<double>& v,
  const double dt,
  double& mean_reversion_rate_hat,
  double& target_mean_hat,
  double& volatility_hat
)
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

  const double mu{
    ((sy * sxx) - (sx * sxy))
     / ( (n_d * (sxx - sxy)) - ( (sx*sx) - (sx*sy)) )
  };

  const double nmu2{n_d*mu*mu};
  //const double nmu2{n_d*n_d*mu*mu};

  const double lambda{
    -std::log(
        (sxy - (mu*sx) - (mu*sy) + nmu2 )
      / (sxx - (2.0*mu*sx) + nmu2)
    ) / dt
  };

  const double a{std::exp(-lambda*dt)};
  const double sigmah2{
    (
      syy
      - (2.0*a*sxy)
      + (a*a*sxx)
      - (2.0*mu*(1.0-a)*(sy - (a*sx)))
      + (nmu2 * (1.0-a)*(1.0-a))
    ) / n_d
  };
  const double sigma{
    std::sqrt(
        (sigmah2 * 2.0 * lambda)
      / (1.0-(a*a))
    )
  };

  mean_reversion_rate_hat = lambda;
  target_mean_hat = mu;
  volatility_hat = sigma;
}

double ribi::OrnsteinUhlenbeck::CalcNext(const double x, const double dt)
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

double ribi::OrnsteinUhlenbeck::CalcNext(
  const double x,
  const double dt,
  const double random_normal
) const
{
  try
  {
    const double term1{x*std::exp(-m_mean_reversion_rate*dt)};
    const double term2{m_target_mean * (1.0-std::exp(-m_mean_reversion_rate*dt))};
    const double term3{m_volatility * random_normal * std::sqrt((1.0 - std::exp(-2.0*m_mean_reversion_rate*dt))  / (2.0 * m_mean_reversion_rate))};
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
void ribi::OrnsteinUhlenbeck::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ///Testing dataset
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

  {
    ///Many thanks to Thijs van den Berg from sitmo.com
    ///to allow for this detailed test
    double x = 3.0;
    OrnsteinUhlenbeck p(mean_reversion_rate,target_mean,volatility);
    const int n{static_cast<int>(noises.size())};
    for (int i=1; i!=n; ++i)
    {
      x = p.CalcNext(x,dt,noises[i]);
      assert(std::abs(x - v[i]) < 0.01);
    }
  }
  //Likelihood
  {
    double ml_mean_reversion_rate{0.01};
    double ml_target_mean{0.0};
    double ml_volatility{0.0};
    CalcMaxLikelihood(v,dt,ml_mean_reversion_rate,ml_target_mean,ml_volatility);
    const double expected_mean_reversion_rate{3.12873217812386};
    const double expected_target_mean{0.90748788828331};
    const double expected_volatility{0.55315453345189};
    if (1 == 2)
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
  }
}
#endif
