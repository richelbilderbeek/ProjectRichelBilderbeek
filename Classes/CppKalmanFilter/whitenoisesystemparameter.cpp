#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "whitenoisesystemparameter.h"


#include <cassert>
#include <stdexcept>
#include <boost/numeric/conversion/cast.hpp>

const std::vector<WhiteNoiseSystemParameterType> WhiteNoiseSystemParameter::GetAll()
{
  const std::vector<WhiteNoiseSystemParameterType> v
    =
    {
      WhiteNoiseSystemParameterType::control,
      WhiteNoiseSystemParameterType::initial_state_real,
      WhiteNoiseSystemParameterType::measurement_frequency,
      WhiteNoiseSystemParameterType::real_measurement_noise,
      WhiteNoiseSystemParameterType::real_process_noise,
      WhiteNoiseSystemParameterType::state_transition,
    };

  assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(WhiteNoiseSystemParameterType::n_parameters)
    && "All parameters must be in");
  return v;
}

bool WhiteNoiseSystemParameter::IsMatrix(const WhiteNoiseSystemParameterType type)
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control: return true;
    case WhiteNoiseSystemParameterType::initial_state_real: return false;
    case WhiteNoiseSystemParameterType::measurement_frequency: return false;
    case WhiteNoiseSystemParameterType::real_measurement_noise: return false;
    case WhiteNoiseSystemParameterType::real_process_noise: return false;
    case WhiteNoiseSystemParameterType::state_transition: return true;
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"n_parameters is not an implemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}

bool WhiteNoiseSystemParameter::IsVector(const WhiteNoiseSystemParameterType type)
{
  return !WhiteNoiseSystemParameter::IsMatrix(type);
}

const std::string WhiteNoiseSystemParameter::ToDescription(const WhiteNoiseSystemParameterType type)
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control:
      return std::string("Matrix for converting input to state change");
    case WhiteNoiseSystemParameterType::initial_state_real:
      return std::string("Vector with the real initial state");
    case WhiteNoiseSystemParameterType::measurement_frequency:
      return std::string("Vector containing after which number of timesteps a measurement is taken");
    case WhiteNoiseSystemParameterType::real_measurement_noise:
      return std::string("Vector with the real standard deviations of the measurement noise per state");
    case WhiteNoiseSystemParameterType::real_process_noise:
      return std::string("Vector with the real standard deviations of the process noise per state");
    case WhiteNoiseSystemParameterType::state_transition:
      return std::string("Matrix that contains the internal physics of the system; the effect of current state on the next state");
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}

const std::string WhiteNoiseSystemParameter::ToName(const WhiteNoiseSystemParameterType type)
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control:
      return std::string("Control");
    case WhiteNoiseSystemParameterType::initial_state_real:
      return std::string("Real initial state");
    case WhiteNoiseSystemParameterType::measurement_frequency:
      return std::string("Measurement frequencies");
    case WhiteNoiseSystemParameterType::real_measurement_noise:
      return std::string("Real measurement noise");
    case WhiteNoiseSystemParameterType::real_process_noise:
      return std::string("Real process noise");
    case WhiteNoiseSystemParameterType::state_transition:
      return std::string("State transition");
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}

const std::string WhiteNoiseSystemParameter::ToSymbol(const WhiteNoiseSystemParameterType type)
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control:
      return std::string("B");
    case WhiteNoiseSystemParameterType::initial_state_real:
      return std::string("x");
    case WhiteNoiseSystemParameterType::measurement_frequency:
      return std::string("f");
    case WhiteNoiseSystemParameterType::real_measurement_noise:
      return std::string("R"); //Shouldn't be 'r', as it is a vector?
    case WhiteNoiseSystemParameterType::real_process_noise:
      return std::string("Q"); //Shouldn't be 'q', as it is a vector?
    case WhiteNoiseSystemParameterType::state_transition:
      return std::string("A");
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}
