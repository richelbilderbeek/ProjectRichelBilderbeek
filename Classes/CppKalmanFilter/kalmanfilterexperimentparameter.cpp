#include "kalmanfilterexperimentparameter.h"

#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

#include "kalmanfilterparameter.h"
#include "whitenoisesystemparameter.h"
#include "testtimer.h"
#include "trace.h"

const std::vector<std::pair<ribi::kalman::KalmanFilterParameterType,ribi::kalman::KalmanFilterExperimentParameterType> >
  ribi::kalman::KalmanFilterExperimentParameter::m_map_kalman_filter = CreateMapKalmanFilter();

const std::vector<std::pair<ribi::kalman::WhiteNoiseSystemParameterType,ribi::kalman::KalmanFilterExperimentParameterType> >
  ribi::kalman::KalmanFilterExperimentParameter::m_map_white_noise_system = CreateMapWhiteNoiseSystem();

ribi::kalman::KalmanFilterExperimentParameter::KalmanFilterExperimentParameter()
{
  #ifndef NDEBUG
  Test();
  #endif
}

bool ribi::kalman::KalmanFilterExperimentParameter::CanConvertToKalmanFilterParameter(
  const KalmanFilterExperimentParameterType parameter) const noexcept
{
  const auto j = m_map_kalman_filter.end();
  for (auto i = m_map_kalman_filter.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return true;
  }
  return false;
}


bool ribi::kalman::KalmanFilterExperimentParameter::CanConvertToWhiteNoiseSystemParameter(
  const KalmanFilterExperimentParameterType parameter) const noexcept
{
  const auto j = m_map_white_noise_system.end();
  for (auto i = m_map_white_noise_system.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return true;
  }
  return false;
}

ribi::kalman::KalmanFilterExperimentParameterType ribi::kalman::KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(
  const KalmanFilterParameterType parameter) const noexcept
{
  const auto j = m_map_kalman_filter.end();
  for (auto i = m_map_kalman_filter.begin(); i!=j ;++i)
  {
    if ((*i).first == parameter) return (*i).second;
  }
  assert(!"Should never get here");
  throw std::logic_error(__func__);
  //throw std::logic_error(
  //  "ribi::kalman::KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(const KalmanFilterParameterType parameter)");
}

ribi::kalman::KalmanFilterExperimentParameterType ribi::kalman::KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(
  const WhiteNoiseSystemParameterType parameter) const noexcept
{
  const auto j = m_map_white_noise_system.end();
  for (auto i = m_map_white_noise_system.begin(); i!=j ;++i)
  {
    if ((*i).first == parameter) return (*i).second;
  }
  assert(!"Should never get here");
  throw std::logic_error(
    "ribi::kalman::KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(const WhiteNoiseSystemParameterType parameter)");
}

ribi::kalman::KalmanFilterParameterType ribi::kalman::KalmanFilterExperimentParameter::ConvertToKalmanFilterParameter(
  const KalmanFilterExperimentParameterType parameter) const noexcept
{
  assert(CanConvertToKalmanFilterParameter(parameter));
  const auto j = m_map_kalman_filter.end();
  for (auto i = m_map_kalman_filter.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return (*i).first;
  }
  assert(!"Should never get here");
  throw std::logic_error(
    "ribi::kalman::KalmanFilterExperimentParameter::ConvertToKalmanFilterParameter");
}

ribi::kalman::WhiteNoiseSystemParameterType ribi::kalman::KalmanFilterExperimentParameter::ConvertToWhiteNoiseSystemParameter(
  const KalmanFilterExperimentParameterType parameter) const noexcept
{
  assert(CanConvertToWhiteNoiseSystemParameter(parameter));
  const auto j = m_map_white_noise_system.end();
  for (auto i = m_map_white_noise_system.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return (*i).first;
  }
  assert(!"Should never get here");
  throw std::logic_error(
    "ribi::kalman::KalmanFilterExperimentParameter::ConvertToWhiteNoiseSystemParameter");
}

const std::vector<std::pair<ribi::kalman::KalmanFilterParameterType,ribi::kalman::KalmanFilterExperimentParameterType> >
  ribi::kalman::KalmanFilterExperimentParameter::CreateMapKalmanFilter()
{
  std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> > v;
  v.push_back(std::make_pair(
    KalmanFilterParameterType::control,
    KalmanFilterExperimentParameterType::control
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::estimated_measurement_noise,
    KalmanFilterExperimentParameterType::estimated_measurement_noise
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::estimated_optimal_kalman_gain,
    KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::estimated_process_noise_covariance,
    KalmanFilterExperimentParameterType::estimated_process_noise_covariance
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::initial_covariance_estimate,
    KalmanFilterExperimentParameterType::initial_covariance_estimate
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::initial_state_estimate,
    KalmanFilterExperimentParameterType::initial_state_estimate
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::observation,
    KalmanFilterExperimentParameterType::observation
  ));
  v.push_back(std::make_pair(
    KalmanFilterParameterType::state_transition,
    KalmanFilterExperimentParameterType::state_transition
  ));
  assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(KalmanFilterParameterType::n_parameters));
  return v;
}

const std::vector<std::pair<ribi::kalman::WhiteNoiseSystemParameterType,ribi::kalman::KalmanFilterExperimentParameterType> >
  ribi::kalman::KalmanFilterExperimentParameter::CreateMapWhiteNoiseSystem()
{
  std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> > v;
  v.push_back(std::make_pair(
    WhiteNoiseSystemParameterType::control,
    KalmanFilterExperimentParameterType::control
  ));
  v.push_back(std::make_pair(
    WhiteNoiseSystemParameterType::initial_state_real,
    KalmanFilterExperimentParameterType::initial_state_real
  ));
  v.push_back(std::make_pair(
    WhiteNoiseSystemParameterType::measurement_frequency,
    KalmanFilterExperimentParameterType::measurement_frequency
  ));
  v.push_back(std::make_pair(
    WhiteNoiseSystemParameterType::real_measurement_noise,
    KalmanFilterExperimentParameterType::real_measurement_noise
  ));
  v.push_back(std::make_pair(
    WhiteNoiseSystemParameterType::real_process_noise,
    KalmanFilterExperimentParameterType::real_process_noise
  ));
  v.push_back(std::make_pair(
    WhiteNoiseSystemParameterType::state_transition,
    KalmanFilterExperimentParameterType::state_transition
  ));
  assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(WhiteNoiseSystemParameterType::n_parameters));
  return v;
}

std::vector<ribi::kalman::KalmanFilterExperimentParameterType>
  ribi::kalman::KalmanFilterExperimentParameter::GetAll() const noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const std::vector<KalmanFilterExperimentParameterType> v
    =
    {
      KalmanFilterExperimentParameterType::control,                            //E K W
      KalmanFilterExperimentParameterType::estimated_measurement_noise,        //E K
      KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain,      //E K
      KalmanFilterExperimentParameterType::estimated_process_noise_covariance, //E K
      KalmanFilterExperimentParameterType::initial_covariance_estimate,        //E K
      KalmanFilterExperimentParameterType::initial_state_estimate,             //E K
      KalmanFilterExperimentParameterType::measurement_frequency,              //E   W
      KalmanFilterExperimentParameterType::initial_state_real,                 //E   W
      KalmanFilterExperimentParameterType::real_measurement_noise,             //E   W
      KalmanFilterExperimentParameterType::real_process_noise,                 //E   W
      KalmanFilterExperimentParameterType::input,                              //E
      KalmanFilterExperimentParameterType::observation,                        //E K
      KalmanFilterExperimentParameterType::state_names,                        //E
      KalmanFilterExperimentParameterType::state_transition                    //E K W
    };

  assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(KalmanFilterExperimentParameterType::n_parameters)
    && "All parameters must be in");
  return v;
}
bool ribi::kalman::KalmanFilterExperimentParameter::IsDouble(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  switch (type)
  {
    case KalmanFilterExperimentParameterType::control:                            return true;
    case KalmanFilterExperimentParameterType::estimated_measurement_noise:        return true;
    case KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain:      return true;
    case KalmanFilterExperimentParameterType::estimated_process_noise_covariance: return true;
    case KalmanFilterExperimentParameterType::initial_covariance_estimate:        return true;
    case KalmanFilterExperimentParameterType::initial_state_estimate:             return true;
    case KalmanFilterExperimentParameterType::initial_state_real:                 return true;
    case KalmanFilterExperimentParameterType::measurement_frequency:              return false;
    case KalmanFilterExperimentParameterType::real_measurement_noise:             return true;
    case KalmanFilterExperimentParameterType::real_process_noise:                 return true;
    case KalmanFilterExperimentParameterType::input:                              return false;
    case KalmanFilterExperimentParameterType::observation:                        return true;
    case KalmanFilterExperimentParameterType::state_names:                        return false;
    case KalmanFilterExperimentParameterType::state_transition:                   return true;
    case KalmanFilterExperimentParameterType::n_parameters:
      assert(!"n_parameters is not implemented to be used");
      throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsDouble: use of n_parameters");
  }
  assert(!"Unimplemented type");
  throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsDouble: use of unimplemented type");
}

bool ribi::kalman::KalmanFilterExperimentParameter::IsFunction(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  switch (type)
  {
    case KalmanFilterExperimentParameterType::control:                            return false;
    case KalmanFilterExperimentParameterType::estimated_measurement_noise:        return false;
    case KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain:      return false;
    case KalmanFilterExperimentParameterType::estimated_process_noise_covariance: return false;
    case KalmanFilterExperimentParameterType::initial_covariance_estimate:        return false;
    case KalmanFilterExperimentParameterType::initial_state_estimate:             return false;
    case KalmanFilterExperimentParameterType::initial_state_real:                 return false;
    case KalmanFilterExperimentParameterType::measurement_frequency:              return false;
    case KalmanFilterExperimentParameterType::real_measurement_noise:             return false;
    case KalmanFilterExperimentParameterType::real_process_noise:                 return false;
    case KalmanFilterExperimentParameterType::input:                              return true;
    case KalmanFilterExperimentParameterType::observation:                        return false;
    case KalmanFilterExperimentParameterType::state_names:                        return false;
    case KalmanFilterExperimentParameterType::state_transition:                   return false;
    case KalmanFilterExperimentParameterType::n_parameters:
      assert(!"n_parameters is not implemented to be used");
      throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsFunction: use of n_parameters");
  }
  assert(!"Unimplemented type");
  throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsFunction: use of unimplemented type");
}

bool ribi::kalman::KalmanFilterExperimentParameter::IsInt(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  switch (type)
  {
    case KalmanFilterExperimentParameterType::control:                            return false;
    case KalmanFilterExperimentParameterType::estimated_measurement_noise:        return false;
    case KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain:      return false;
    case KalmanFilterExperimentParameterType::estimated_process_noise_covariance: return false;
    case KalmanFilterExperimentParameterType::initial_covariance_estimate:        return false;
    case KalmanFilterExperimentParameterType::initial_state_estimate:             return false;
    case KalmanFilterExperimentParameterType::initial_state_real:                 return false;
    case KalmanFilterExperimentParameterType::measurement_frequency:              return true;
    case KalmanFilterExperimentParameterType::real_measurement_noise:             return false;
    case KalmanFilterExperimentParameterType::real_process_noise:                 return false;
    case KalmanFilterExperimentParameterType::input:                              return false;
    case KalmanFilterExperimentParameterType::observation:                        return false;
    case KalmanFilterExperimentParameterType::state_names:                        return false;
    case KalmanFilterExperimentParameterType::state_transition:                   return false;
    case KalmanFilterExperimentParameterType::n_parameters:
      assert(!"n_parameters is not implemented to be used");
      throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsInt: use of n_parameters");
  }
  assert(!"Unimplemented type");
  throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsInt: use of unimplemented type");
}

bool ribi::kalman::KalmanFilterExperimentParameter::IsString(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  switch (type)
  {
    case KalmanFilterExperimentParameterType::control:                            return false;
    case KalmanFilterExperimentParameterType::estimated_measurement_noise:        return false;
    case KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain:      return false;
    case KalmanFilterExperimentParameterType::estimated_process_noise_covariance: return false;
    case KalmanFilterExperimentParameterType::initial_covariance_estimate:        return false;
    case KalmanFilterExperimentParameterType::initial_state_estimate:             return false;
    case KalmanFilterExperimentParameterType::initial_state_real:                 return false;
    case KalmanFilterExperimentParameterType::measurement_frequency:              return false;
    case KalmanFilterExperimentParameterType::real_measurement_noise:             return false;
    case KalmanFilterExperimentParameterType::real_process_noise:                 return false;
    case KalmanFilterExperimentParameterType::input:                              return true;
    case KalmanFilterExperimentParameterType::observation:                        return false;
    case KalmanFilterExperimentParameterType::state_names:                        return true;
    case KalmanFilterExperimentParameterType::state_transition:                   return false;
    case KalmanFilterExperimentParameterType::n_parameters:
      assert(!"n_parameters is not implemented to be used");
      throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsString: use of n_parameters");
  }
  assert(!"Unimplemented type");
  throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsString: use of unimplemented type");
}

bool ribi::kalman::KalmanFilterExperimentParameter::IsMatrix(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  return !ribi::kalman::KalmanFilterExperimentParameter::IsVector(type);
}

bool ribi::kalman::KalmanFilterExperimentParameter::IsVector(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  switch (type)
  {
    case KalmanFilterExperimentParameterType::control:                            return false;
    case KalmanFilterExperimentParameterType::estimated_measurement_noise:        return false;
    case KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain:      return false;
    case KalmanFilterExperimentParameterType::estimated_process_noise_covariance: return false;
    case KalmanFilterExperimentParameterType::initial_covariance_estimate:        return false;
    case KalmanFilterExperimentParameterType::initial_state_estimate:             return true;
    case KalmanFilterExperimentParameterType::initial_state_real:                 return true;
    case KalmanFilterExperimentParameterType::measurement_frequency:              return true;
    case KalmanFilterExperimentParameterType::real_measurement_noise:             return true;
    case KalmanFilterExperimentParameterType::real_process_noise:                 return true;
    case KalmanFilterExperimentParameterType::input:                              return true;
    case KalmanFilterExperimentParameterType::observation:                        return false;
    case KalmanFilterExperimentParameterType::state_names:                        return true;
    case KalmanFilterExperimentParameterType::state_transition:                   return false;
    case KalmanFilterExperimentParameterType::n_parameters:
      assert(!"n_parameters is not implemented to be used");
      throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsVector: use of n_parameters");
  }
  assert(!"Unimplemented type");
  throw std::logic_error("ribi::kalman::KalmanFilterExperimentParameter::IsVector: use of unimplemented type");
}

#ifndef NDEBUG
void ribi::kalman::KalmanFilterExperimentParameter::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  KalmanFilterExperimentParameter p;
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::control));
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::initial_state_real));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::measurement_frequency));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::real_process_noise));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::input));
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::observation));
  assert(!p.IsMatrix(KalmanFilterExperimentParameterType::state_names));
  assert( p.IsMatrix(KalmanFilterExperimentParameterType::state_transition));

  assert(!p.IsVector(KalmanFilterExperimentParameterType::control));
  assert(!p.IsVector(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert(!p.IsVector(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert(!p.IsVector(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert(!p.IsVector(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert( p.IsVector(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert( p.IsVector(KalmanFilterExperimentParameterType::initial_state_real));
  assert( p.IsVector(KalmanFilterExperimentParameterType::measurement_frequency));
  assert( p.IsVector(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert( p.IsVector(KalmanFilterExperimentParameterType::real_process_noise));
  assert( p.IsVector(KalmanFilterExperimentParameterType::input));
  assert(!p.IsVector(KalmanFilterExperimentParameterType::observation));
  assert( p.IsVector(KalmanFilterExperimentParameterType::state_names));
  assert(!p.IsVector(KalmanFilterExperimentParameterType::state_transition));

  assert(!p.IsString(KalmanFilterExperimentParameterType::control));
  assert(!p.IsString(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert(!p.IsString(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert(!p.IsString(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert(!p.IsString(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert(!p.IsString(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert(!p.IsString(KalmanFilterExperimentParameterType::initial_state_real));
  assert(!p.IsString(KalmanFilterExperimentParameterType::measurement_frequency));
  assert(!p.IsString(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert(!p.IsString(KalmanFilterExperimentParameterType::real_process_noise));
  assert( p.IsString(KalmanFilterExperimentParameterType::input));
  assert(!p.IsString(KalmanFilterExperimentParameterType::observation));
  assert( p.IsString(KalmanFilterExperimentParameterType::state_names));
  assert(!p.IsString(KalmanFilterExperimentParameterType::state_transition));

  assert(!p.IsFunction(KalmanFilterExperimentParameterType::control));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::initial_state_real));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::measurement_frequency));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::real_process_noise));
  assert( p.IsFunction(KalmanFilterExperimentParameterType::input));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::observation));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::state_names));
  assert(!p.IsFunction(KalmanFilterExperimentParameterType::state_transition));

  assert( p.IsDouble(KalmanFilterExperimentParameterType::control));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::initial_state_real));
  assert(!p.IsDouble(KalmanFilterExperimentParameterType::measurement_frequency));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::real_process_noise));
  assert(!p.IsDouble(KalmanFilterExperimentParameterType::input));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::observation));
  assert(!p.IsDouble(KalmanFilterExperimentParameterType::state_names));
  assert( p.IsDouble(KalmanFilterExperimentParameterType::state_transition));

  assert(!p.IsInt(KalmanFilterExperimentParameterType::control));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::initial_state_real));
  assert( p.IsInt(KalmanFilterExperimentParameterType::measurement_frequency));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::real_process_noise));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::input));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::observation));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::state_names));
  assert(!p.IsInt(KalmanFilterExperimentParameterType::state_transition));

}
#endif

std::string ribi::kalman::KalmanFilterExperimentParameter::ToDescription(
  const KalmanFilterExperimentParameterType type
) const noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  //Check for the subset
  if (CanConvertToKalmanFilterParameter(type))
  {
    const KalmanFilterParameterType sub_type = ConvertToKalmanFilterParameter(type);
    return KalmanFilterParameter().ToDescription(sub_type);
  }
  if (CanConvertToWhiteNoiseSystemParameter(type))
  {
    const WhiteNoiseSystemParameterType sub_type = ConvertToWhiteNoiseSystemParameter(type);
    return WhiteNoiseSystemParameter().ToDescription(sub_type);
  }
  //Check the unique types
  switch (type)
  {
    case KalmanFilterExperimentParameterType::input:
      return "Vector of inputs";
    case KalmanFilterExperimentParameterType::state_names:
      return "Vector of the state element names";
    default: assert(!"Unimplemented type of KalmanFilterExperimentParameterType");
      throw std::logic_error(__func__);
  }
}

std::string ribi::kalman::KalmanFilterExperimentParameter::ToName(const KalmanFilterExperimentParameterType type) const noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  //Check for the subset
  if (CanConvertToKalmanFilterParameter(type))
  {
    const KalmanFilterParameterType sub_type = ConvertToKalmanFilterParameter(type);
    return KalmanFilterParameter().ToName(sub_type);
  }
  if (CanConvertToWhiteNoiseSystemParameter(type))
  {
    const WhiteNoiseSystemParameterType sub_type = ConvertToWhiteNoiseSystemParameter(type);
    return WhiteNoiseSystemParameter().ToName(sub_type);
  }
  //Check the unique types
  switch (type)
  {
    case KalmanFilterExperimentParameterType::input:
      return "Input";
    case KalmanFilterExperimentParameterType::state_names:
      return "State names";
    default: assert(!"Unimplemented type of KalmanFilterExperimentParameterType");
      throw std::logic_error(__func__);
  }
}

  std::string ribi::kalman::KalmanFilterExperimentParameter::ToSymbol(const KalmanFilterExperimentParameterType type) const noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  //Check for the subset
  if (CanConvertToKalmanFilterParameter(type))
  {
    const KalmanFilterParameterType sub_type = ConvertToKalmanFilterParameter(type);
    return KalmanFilterParameter().ToSymbol(sub_type);
  }
  if (CanConvertToWhiteNoiseSystemParameter(type))
  {
    const WhiteNoiseSystemParameterType sub_type = ConvertToWhiteNoiseSystemParameter(type);
    return WhiteNoiseSystemParameter().ToSymbol(sub_type);
  }
  //Check the unique types
  switch (type)
  {
    case KalmanFilterExperimentParameterType::input:
      return "y";
    case KalmanFilterExperimentParameterType::state_names:
      return ""; //State names has no symbol
    default: assert(!"Unimplemented type of KalmanFilterExperimentParameterType");
      throw std::logic_error(__func__);
  }
}
