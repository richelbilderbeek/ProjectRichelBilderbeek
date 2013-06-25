#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
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
    m_parameters(boost::dynamic_pointer_cast<const GapsFilledWhiteNoiseSystemParameters>(parameters)),
    m_timestep(0)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_parameters);
  assert(m_parameters->GetGap() >= 1 && "At least 1 out of 1 measurements is given");
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
  this->GoToNextState(input);
}

const boost::numeric::ublas::vector<double> GapsFilledWhiteNoiseSystem::Measure() const
{
  assert(m_parameters->GetGap() >= 1);

  if (m_timestep % m_parameters->GetGap() == 0)
  {
    m_last_measument = this->Measure();
  }
  ++m_timestep;
  return m_last_measument;
}

const boost::numeric::ublas::vector<double>& GapsFilledWhiteNoiseSystem::PeekAtRealState() const
{
  return this->PeekAtRealState();
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
    const int gap = 5;
    const boost::shared_ptr<GapsFilledWhiteNoiseSystem> my_system
      = GapsFilledWhiteNoiseSystemFactory::Create(
        Matrix::CreateMatrix(1,1, { 1.0 } ), //control
        gap,
        Matrix::CreateVector(     { 0.0 } ), //initial_state,
        Matrix::CreateVector(     { 0.0 } ), //real_measurement_noise
        Matrix::CreateVector(     { 0.0 } ), //real_process_noise
        Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    );
    const boost::numeric::ublas::vector<double> input = Matrix::CreateVector( { 1.0 } );

    for (int i=0; i!=gap; ++i)
    {
      assert(Matrix::IsAboutEqual( my_system->Measure()(0), 0.0));
      assert(Matrix::IsAboutEqual( my_system->PeekAtRealState()(0), boost::numeric_cast<double>(i) ) );
      my_system->GoToNextState(input);
    }
    for (int i=0; i!=10; ++i) //10 = just some value
    {
      const double expected = boost::numeric_cast<double>(i);
      assert(Matrix::IsAboutEqual( my_system->Measure()(0), expected));
      assert(Matrix::IsAboutEqual( my_system->PeekAtRealState()(0), boost::numeric_cast<double>(gap + i) ) );
      my_system->GoToNextState(input);
    }
  }
  TRACE("Finished GapsFilledWhiteNoiseSystem::Test()")
}
#endif
