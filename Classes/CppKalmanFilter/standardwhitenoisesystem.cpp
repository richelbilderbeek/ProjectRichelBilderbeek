#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "standardwhitenoisesystem.h"

#include <iostream>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>
#pragma GCC diagnostic pop

#include "matrix.h"
#include "trace.h"
#include "standardwhitenoisesystemparameters.h"

ribi::kalman::StandardWhiteNoiseSystem::StandardWhiteNoiseSystem(
  const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters)
  : WhiteNoiseSystem{parameters},
    m_parameters{boost::dynamic_pointer_cast<const StandardWhiteNoiseSystemParameters>(parameters)}
{
  assert(m_parameters);
}

std::string ribi::kalman::StandardWhiteNoiseSystem::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::kalman::StandardWhiteNoiseSystem::GetVersionHistory() noexcept
{
  return {
    "2013-04-28: version 1.0: initial version"
  };
}

void ribi::kalman::StandardWhiteNoiseSystem::GoToNextState()
{
  //Create a no-input vector
  const auto sz = GetCurrentState().size();
  boost::numeric::ublas::vector<double> input(sz,0.0);
  return GoToNextState(input);
}

void ribi::kalman::StandardWhiteNoiseSystem::GoToNextState(const boost::numeric::ublas::vector<double>& input)
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

boost::numeric::ublas::vector<double> ribi::kalman::StandardWhiteNoiseSystem::Measure() const noexcept
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
