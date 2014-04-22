#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "whitenoisesystemparameter.h"

#include <cassert>
#include <stdexcept>
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

std::vector<ribi::kalman::WhiteNoiseSystemParameterType> ribi::kalman::WhiteNoiseSystemParameter::GetAll() noexcept
{
  const std::vector<WhiteNoiseSystemParameterType> v {
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

bool ribi::kalman::WhiteNoiseSystemParameter::IsMatrix(const WhiteNoiseSystemParameterType type) noexcept
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

bool ribi::kalman::WhiteNoiseSystemParameter::IsVector(const WhiteNoiseSystemParameterType type) noexcept
{
  return !ribi::kalman::WhiteNoiseSystemParameter::IsMatrix(type);
}

std::string ribi::kalman::WhiteNoiseSystemParameter::ToDescription(const WhiteNoiseSystemParameterType type) noexcept
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control:
      return "Matrix for converting input to state change";
    case WhiteNoiseSystemParameterType::initial_state_real:
      return "Vector with the real initial state";
    case WhiteNoiseSystemParameterType::measurement_frequency:
      return "Vector containing after which number of timesteps a measurement is taken";
    case WhiteNoiseSystemParameterType::real_measurement_noise:
      return "Vector with the real standard deviations of the measurement noise per state";
    case WhiteNoiseSystemParameterType::real_process_noise:
      return "Vector with the real standard deviations of the process noise per state";
    case WhiteNoiseSystemParameterType::state_transition:
      return "Matrix that contains the internal physics of the system; the effect of current state on the next state";
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}

std::string ribi::kalman::WhiteNoiseSystemParameter::ToName(const WhiteNoiseSystemParameterType type) noexcept
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control:
      return "Control";
    case WhiteNoiseSystemParameterType::initial_state_real:
      return "Real initial state";
    case WhiteNoiseSystemParameterType::measurement_frequency:
      return "Measurement frequencies";
    case WhiteNoiseSystemParameterType::real_measurement_noise:
      return "Real measurement noise";
    case WhiteNoiseSystemParameterType::real_process_noise:
      return "Real process noise";
    case WhiteNoiseSystemParameterType::state_transition:
      return "State transition";
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}

std::string ribi::kalman::WhiteNoiseSystemParameter::ToSymbol(const WhiteNoiseSystemParameterType type) noexcept
{
  switch (type)
  {
    case WhiteNoiseSystemParameterType::control:
      return "B";
    case WhiteNoiseSystemParameterType::initial_state_real:
      return "x";
    case WhiteNoiseSystemParameterType::measurement_frequency:
      return "f";
    case WhiteNoiseSystemParameterType::real_measurement_noise:
      return "R"; //Shouldn't be 'r', as it is a vector?
    case WhiteNoiseSystemParameterType::real_process_noise:
      return "Q"; //Shouldn't be 'q', as it is a vector?
    case WhiteNoiseSystemParameterType::state_transition:
      return "A";
    case WhiteNoiseSystemParameterType::n_parameters:
      assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of WhiteNoiseSystemParameterType");
  throw std::logic_error(__func__);
}
