#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "gapsfilledwhitenoisesystem.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>

#include "matrix.h"
#include "trace.h"
#include "gapsfilledwhitenoisesystem.h"
#include "gapsfilledwhitenoisesystemfactory.h"
#include "gapsfilledwhitenoisesystemparameters.h"

GapsFilledWhiteNoiseSystem::GapsFilledWhiteNoiseSystem(
  const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters)
  : WhiteNoiseSystem(parameters),
    m_last_measument(parameters->GetInitialState().size(),0.0),
    m_parameters(boost::dynamic_pointer_cast<const GapsFilledWhiteNoiseSystemParameters>(parameters)),
    m_timestep(0)
{
  #ifndef NDEBUG
  Test();
  assert(m_parameters);
  //Check measuring frequecies
  {
    const auto v = m_parameters->GetMeasurementFrequency();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const int x = v[i];
      assert(x >= 1 && "At least one out of one measurements is a real measurement");
    }
  }
  #endif
}

const std::string GapsFilledWhiteNoiseSystem::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> GapsFilledWhiteNoiseSystem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-25: version 1.0: initial version");
  return v;
}

void GapsFilledWhiteNoiseSystem::GoToNextState(const boost::numeric::ublas::vector<double>& input)
{
  //Standard transition
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

const boost::numeric::ublas::vector<double> GapsFilledWhiteNoiseSystem::Measure() const
{
  const boost::numeric::ublas::vector<int>& fs
    = this->GetGapsFilledWhiteNoiseSystemParameters()->GetMeasurementFrequency();

  assert(fs.size() == m_last_measument.size());
  assert(fs.size() == GetCurrentState().size());
  assert(fs.size() == m_parameters->GetMeasurementNoise().size());

  const std::size_t n_states = fs.size();
  for (std::size_t state=0; state!=n_states; ++state)
  {
    assert(state < fs.size());
    const int f = fs[state];
    assert(f >= 1);

    if (m_timestep % f == 0)
    {
      assert(state < m_last_measument.size());
      assert(state < GetCurrentState().size());
      assert(state < m_parameters->GetMeasurementNoise().size());
      m_last_measument(state) = GetRandomNormal(GetCurrentState()(state),m_parameters->GetMeasurementNoise()(state));
    }
    else
    {
      //Should get here
    }
  }
  ++m_timestep;

  return m_last_measument;
}

const boost::numeric::ublas::vector<double>& GapsFilledWhiteNoiseSystem::PeekAtRealState() const
{
  return this->GetCurrentState();
}

#ifndef NDEBUG
void GapsFilledWhiteNoiseSystem::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting GapsFilledWhiteNoiseSystem::Test()")
  //Check if measurements are indeed lagged:
  //The system's real value should update immediatly, but this fresh measurement
  //must only be accessible after lag timesteps
  //Context: measuring the position of an object with constant velocity
  {
    const int f = 5;
    const boost::shared_ptr<GapsFilledWhiteNoiseSystem> my_system
      = GapsFilledWhiteNoiseSystemFactory::Create(
        Matrix::CreateMatrix(1,1, { 1.0 } ), //control
        Matrix::CreateVector(     { 0.0 } ), //initial_state,
        Matrix::CreateVector(     {   f } ), //measurement frequencies
        Matrix::CreateVector(     { 0.0000001 } ), //real_measurement_noise
        Matrix::CreateVector(     { 0.0000001 } ), //real_process_noise
        Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    );
    assert(my_system);
    //Context: airhockey puck
    const boost::numeric::ublas::vector<double> input = Matrix::CreateVector( { 1.0 } );

    for (int i=0; i!= 3*f; ++i)
    {
      const boost::numeric::ublas::vector<double> measurements = my_system->Measure();
      assert(!measurements.empty());
      assert(measurements.size() == 1);
      assert(measurements.size() == my_system->PeekAtRealState().size());
      const double expected = static_cast<double>(i);
      const double measured = measurements(0);
      const double real = my_system->PeekAtRealState()(0);
      assert(Matrix::IsAboutEqual(real,expected));
      if (i % f == 0)
      {
        assert(Matrix::IsAboutEqual(measured,expected));
      }
      else
      {
        assert(!Matrix::IsAboutEqual(measured,expected));
      }
      my_system->GoToNextState(input);
    }
  }
  TRACE("Finished GapsFilledWhiteNoiseSystem::Test()")
}
#endif
