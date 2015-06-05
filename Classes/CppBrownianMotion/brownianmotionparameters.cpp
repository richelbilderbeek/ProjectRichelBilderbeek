#include "brownianmotionparameters.h"

#include <sstream>
#include <stdexcept>


ribi::bm::Parameters::Parameters(
  const Volatility volatility,
  const int rng_seed
) : m_rng_seed{rng_seed},
    m_volatility{volatility}
{
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
