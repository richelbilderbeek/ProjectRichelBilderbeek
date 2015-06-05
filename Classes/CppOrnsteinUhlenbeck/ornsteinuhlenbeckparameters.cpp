#include "ornsteinuhlenbeckparameters.h"

#include <sstream>
#include <stdexcept>

ribi::ou::Parameters::Parameters(
  const Rate mean_reversion_rate,
  const double target_mean,
  const Rate volatility,
  const int rng_seed
)
  :
    m_mean_reversion_rate{mean_reversion_rate},
    m_rng_seed{rng_seed},
    m_target_mean{target_mean},
    m_volatility{volatility}
{
  //TODO: allow zero, then the process falls back to a Brownian process
  if (m_mean_reversion_rate <= 0.0 / boost::units::si::second)
  {
    std::stringstream s;
    s << __func__
      << ": mean reversion rate must be positive and non-zero, "
      << "value given is " << m_mean_reversion_rate
    ;
    throw std::logic_error(s.str());
  }

  //TODO: allow zero, then the process falls back to an autoregression
  if (m_volatility <= 0.0 / boost::units::si::second)
  {
    std::stringstream s;
    s << __func__
      << ": volatility must be positive and non-zero, "
      << "value given is " << m_volatility
    ;
    throw std::logic_error(s.str());
  }
}

