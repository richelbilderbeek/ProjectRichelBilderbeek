#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "standardwhitenoisesystem.h"

#include <iostream>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>

#include "matrix.h"
#include "trace.h"
#include "standardwhitenoisesystemparameters.h"

StandardWhiteNoiseSystem::StandardWhiteNoiseSystem(
  const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters)
  : WhiteNoiseSystem(parameters),
    m_parameters(boost::dynamic_pointer_cast<const StandardWhiteNoiseSystemParameters>(parameters))
{
  assert(m_parameters);
}

const std::string StandardWhiteNoiseSystem::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> StandardWhiteNoiseSystem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-04-28: version 1.0: initial version");
  return v;
}

void StandardWhiteNoiseSystem::GoToNextState()
{
  //Create a no-input vector
  const auto sz = GetCurrentState().size();
  boost::numeric::ublas::vector<double> input(sz,0.0);
  return GoToNextState(input);
}

void StandardWhiteNoiseSystem::GoToNextState(const boost::numeric::ublas::vector<double>& input)
{
  //First do a perfect transition
  assert(input.size() == GetCurrentState().size());
  assert(m_parameters->GetStateTransition().size1() == GetCurrentState().size());
  assert(m_parameters->GetStateTransition().size2() == GetCurrentState().size());
  assert(m_parameters->GetControl().size1() == input.size());
  assert(m_parameters->GetControl().size2() == input.size());

  boost::numeric::ublas::vector<double> new_state
    = Matrix::Prod(m_parameters->GetStateTransition(),GetCurrentState())
    + Matrix::Prod(m_parameters->GetControl(),input);
  //Add process noise
  const auto sz = new_state.size();
  assert(new_state.size() == m_parameters->GetProcessNoise().size());
  for (std::size_t i = 0; i!=sz; ++i)
  {
    new_state(i) = GetRandomNormal(new_state(i),m_parameters->GetProcessNoise()(i));
  }
  SetNewCurrentState(new_state);
}

const boost::numeric::ublas::vector<double> StandardWhiteNoiseSystem::Measure() const
{
  const auto sz = GetCurrentState().size();
  assert(GetCurrentState().size() == m_parameters->GetMeasurementNoise().size());
  boost::numeric::ublas::vector<double> measured(sz);
  for (std::size_t i = 0; i!=sz; ++i)
  {
    measured(i) = GetRandomNormal(GetCurrentState()(i),m_parameters->GetMeasurementNoise()(i));
  }
  return measured;
}
