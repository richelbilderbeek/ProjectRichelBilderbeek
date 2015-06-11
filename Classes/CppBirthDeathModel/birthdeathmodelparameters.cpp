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
    m_time{time},
    m_n_taxa{0}
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

ribi::bdm::Parameters::Parameters(
    const BirthRate birth_rate,
    const DeathRate death_rate,
    const int n_taxa,
    const int rng_seed
) :
    m_birth_rate{birth_rate},
    m_death_rate{death_rate},
    m_rng_seed{rng_seed},
    m_time{0.0 * boost::units::si::second},
    m_n_taxa{n_taxa}
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
  if (m_n_taxa < 2)
  {
    std::stringstream s;
    s << __func__
      << ": n_taxa must be 2 at least, "
      << "value given is " << m_n_taxa
    ;
    throw std::logic_error(s.str());
  }

}
