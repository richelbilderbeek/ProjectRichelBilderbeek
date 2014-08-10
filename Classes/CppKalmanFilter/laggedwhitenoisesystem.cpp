#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "laggedwhitenoisesystem.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

#include "matrix.h"
#include "trace.h"
#include "laggedwhitenoisesystem.h"
#include "laggedwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystemparameters.h"
#include "standardwhitenoisesystemparameters.h"
#include "standardwhitenoisesystemfactory.h"
#include "testtimer.h"

ribi::kalman::LaggedWhiteNoiseSystem::LaggedWhiteNoiseSystem(
  const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters)
  : WhiteNoiseSystem{parameters},
    m_measuments{},
    m_parameters{boost::dynamic_pointer_cast<const LaggedWhiteNoiseSystemParameters>(parameters)},
    m_system{
      StandardWhiteNoiseSystemFactory().Create(
        parameters->GetControl(),
        parameters->GetInitialState(),
        parameters->GetMeasurementNoise(),
        parameters->GetProcessNoise(),
        parameters->GetStateTransition()
      )
    }
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_parameters);
  assert(m_parameters->GetLag() >= 0);
  assert(boost::numeric_cast<int>(m_measuments.size()) <= m_parameters->GetLag());
  assert(m_system);

  const int lag = m_parameters->GetLag();
  while (lag != boost::numeric_cast<int>(m_measuments.size()))
  {
    m_measuments.push(m_system->Measure());
  }
  assert(lag == boost::numeric_cast<int>(m_measuments.size()));
}

std::string ribi::kalman::LaggedWhiteNoiseSystem::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::kalman::LaggedWhiteNoiseSystem::GetVersionHistory() noexcept
{
  return {
    "2013-05-03: version 1.0: initial version"
  };
}

void ribi::kalman::LaggedWhiteNoiseSystem::GoToNextState(const boost::numeric::ublas::vector<double>& input)
{
  m_system->GoToNextState(input);
}

boost::numeric::ublas::vector<double> ribi::kalman::LaggedWhiteNoiseSystem::Measure() const noexcept
{
  assert(m_parameters->GetLag() == boost::numeric_cast<int>(m_measuments.size()));
  m_measuments.push(m_system->Measure());

  //Result is copied now, to also work for m_lag == 0
  const boost::numeric::ublas::vector<double> result = m_measuments.front();

  m_measuments.pop();
  assert(m_parameters->GetLag() == boost::numeric_cast<int>(m_measuments.size()));
  return result;
}

const boost::numeric::ublas::vector<double>& ribi::kalman::LaggedWhiteNoiseSystem::PeekAtRealState() const noexcept
{
  return m_system->PeekAtRealState();
}

#ifndef NDEBUG
void ribi::kalman::LaggedWhiteNoiseSystem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Check if measurements are indeed lagged:
  //The system's real value should update immediatly, but this fresh measurement
  //must only be accessible after lag timesteps
  //Context: measuring the position of an object with constant velocity
  {
    const int lag = 5;
    const boost::shared_ptr<LaggedWhiteNoiseSystem> my_system
      = LaggedWhiteNoiseSystemFactory().Create(
        Matrix::CreateMatrix(1,1, { 1.0 } ), //control
        Matrix::CreateVector(     { 0.0 } ), //initial_state,
        lag,
        Matrix::CreateVector(     { 0.0 } ), //real_measurement_noise
        Matrix::CreateVector(     { 0.0 } ), //real_process_noise
        Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    );
    const boost::numeric::ublas::vector<double> input = Matrix::CreateVector( { 1.0 } );

    for (int i=0; i!=lag; ++i)
    {
      assert(Matrix::IsAboutEqual( my_system->Measure()(0), 0.0));
      assert(Matrix::IsAboutEqual( my_system->PeekAtRealState()(0), boost::numeric_cast<double>(i) ) );
      my_system->GoToNextState(input);
    }
    for (int i=0; i!=10; ++i) //10 = just some value
    {
      const double expected = boost::numeric_cast<double>(i);
      assert(Matrix::IsAboutEqual( my_system->Measure()(0), expected));
      assert(Matrix::IsAboutEqual( my_system->PeekAtRealState()(0), boost::numeric_cast<double>(lag + i) ) );
      my_system->GoToNextState(input);
    }
  }
}
#endif
