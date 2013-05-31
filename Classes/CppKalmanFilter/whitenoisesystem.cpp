#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "whitenoisesystem.h"

#include <cassert>
#include <boost/random.hpp>


WhiteNoiseSystem::WhiteNoiseSystem(const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters)
  : m_current_state(parameters->GetInitialState()),
    m_parameters(parameters)
{
  assert(m_parameters);
}

double WhiteNoiseSystem::GetRandomNormal(const double mean, const double sigma)
{
  boost::normal_distribution<double> norm_dist(mean, sigma);
  static boost::lagged_fibonacci19937 engine;
  const double value = norm_dist.operator () <boost::lagged_fibonacci19937>((engine));
  return value;
}

const std::string WhiteNoiseSystem::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> WhiteNoiseSystem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-05-03: version 1.0: initial version");
  return v;
}

void WhiteNoiseSystem::SetNewCurrentState(const boost::numeric::ublas::vector<double>& new_current_state)
{
  assert(m_current_state.size() == new_current_state.size());
  m_current_state = new_current_state;
}
