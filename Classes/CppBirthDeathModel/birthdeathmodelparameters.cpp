#include "birthdeathmodelparameters.h"

#include <sstream>
#include <stdexcept>

ribi::bdm::Parameters::Parameters(
    const BirthRate birth_rate,
    const DeathRate death_rate,
    const Time time,
    const int rng_seed
) :
    m_birth_rate{birth_rate},
    m_death_rate{death_rate},
    m_rng_seed{rng_seed},
    m_time{time}
{
  if (m_birth_rate < 0.0 / boost::units::si::second)
  {
    std::stringstream s;
    s << __func__
      << ": birth_rate must be positive, "
      << "value given is " << m_birth_rate
    ;
    throw std::logic_error(s.str());
  }
  if (m_death_rate < 0.0 / boost::units::si::second)
  {
    std::stringstream s;
    s << __func__
      << ": death_rate must be positive, "
      << "value given is " << m_death_rate
    ;
    throw std::logic_error(s.str());
  }
  if (m_time < 0.0 * boost::units::si::second)
  {
    std::stringstream s;
    s << __func__
      << ": time must be positive, "
      << "value given is " << m_time
    ;
    throw std::logic_error(s.str());
  }

}
