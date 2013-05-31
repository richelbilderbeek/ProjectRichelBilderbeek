#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfilterexperimentparameter.h"

#include <cassert>
#include <stdexcept>
#include <boost/numeric/conversion/cast.hpp>

#include "kalmanfilterparameter.h"
#include "whitenoisesystemparameter.h"
#include "trace.h"

const std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> >
  KalmanFilterExperimentParameter::m_map_kalman_filter = CreateMapKalmanFilter();

const std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> >
  KalmanFilterExperimentParameter::m_map_white_noise_system = CreateMapWhiteNoiseSystem();

bool KalmanFilterExperimentParameter::CanConvertToKalmanFilterParameter(
  const KalmanFilterExperimentParameterType parameter)
{
  const auto j = m_map_kalman_filter.end();
  for (auto i = m_map_kalman_filter.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return true;
  }
  return false;
}


bool KalmanFilterExperimentParameter::CanConvertToWhiteNoiseSystemParameter(
  const KalmanFilterExperimentParameterType parameter)
{
  const auto j = m_map_white_noise_system.end();
  for (auto i = m_map_white_noise_system.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return true;
  }
  return false;
}

KalmanFilterExperimentParameterType KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(
  const KalmanFilterParameterType parameter)
{
  const auto j = m_map_kalman_filter.end();
  for (auto i = m_map_kalman_filter.begin(); i!=j ;++i)
  {
    if ((*i).first == parameter) return (*i).second;
  }
  assert(!"Should never get here");
  throw std::logic_error(__func__);
  //throw std::logic_error(
  //  "KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(const KalmanFilterParameterType parameter)");
}

KalmanFilterExperimentParameterType KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(
  const WhiteNoiseSystemParameterType parameter)
{
  const auto j = m_map_white_noise_system.end();
  for (auto i = m_map_white_noise_system.begin(); i!=j ;++i)
  {
    if ((*i).first == parameter) return (*i).second;
  }
  assert(!"Should never get here");
  throw std::logic_error(
    "KalmanFilterExperimentParameter::ConvertToKalmanFilterExperimentParameter(const WhiteNoiseSystemParameterType parameter)");
}

KalmanFilterParameterType KalmanFilterExperimentParameter::ConvertToKalmanFilterParameter(
  const KalmanFilterExperimentParameterType parameter)
{
  assert(CanConvertToKalmanFilterParameter(parameter));
  const auto j = m_map_kalman_filter.end();
  for (auto i = m_map_kalman_filter.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return (*i).first;
  }
  assert(!"Should never get here");
  throw std::logic_error(
    "KalmanFilterExperimentParameter::ConvertToKalmanFilterParameter");
}

WhiteNoiseSystemParameterType KalmanFilterExperimentParameter::ConvertToWhiteNoiseSystemParameter(
  const KalmanFilterExperimentParameterType parameter)
{
  assert(CanConvertToWhiteNoiseSystemParameter(parameter));
  const auto j = m_map_white_noise_system.end();
  for (auto i = m_map_white_noise_system.begin(); i!=j ;++i)
  {
    if ((*i).second == parameter) return (*i).first;
  }
  assert(!"Should never get here");
  throw std::logic_error(
    "KalmanFilterExperimentParameter::ConvertToWhiteNoiseSystemParameter");
}

const std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> >
  KalmanFilterExperimentParameter::CreateMapKalmanFilter()
{
  #ifndef NDEBUG
  Test();
  #endif

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

const std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> >
  KalmanFilterExperimentParameter::CreateMapWhiteNoiseSystem()
{
  #ifndef NDEBUG
  Test();
  #endif
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

const std::vector<KalmanFilterExperimentParameterType> KalmanFilterExperimentParameter::GetAll()
{
  const std::vector<KalmanFilterExperimentParameterType> v
    =
    {
      KalmanFilterExperimentParameterType::control,                            //E K W
      KalmanFilterExperimentParameterType::estimated_measurement_noise,        //E K
      KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain,      //E K
      KalmanFilterExperimentParameterType::estimated_process_noise_covariance, //E K
      KalmanFilterExperimentParameterType::initial_covariance_estimate,        //E K
      KalmanFilterExperimentParameterType::initial_state_estimate,             //E K
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
bool KalmanFilterExperimentParameter::IsDouble(const KalmanFilterExperimentParameterType type)
{
  return !IsString(type);
}

bool KalmanFilterExperimentParameter::IsFunction(const KalmanFilterExperimentParameterType type)
{
  return type == KalmanFilterExperimentParameterType::input;
}

bool KalmanFilterExperimentParameter::IsString(const KalmanFilterExperimentParameterType type)
{
  return type == KalmanFilterExperimentParameterType::input
    || type == KalmanFilterExperimentParameterType::state_names;
}

bool KalmanFilterExperimentParameter::IsMatrix(const KalmanFilterExperimentParameterType type)
{
  return !KalmanFilterExperimentParameter::IsVector(type);
}

bool KalmanFilterExperimentParameter::IsVector(const KalmanFilterExperimentParameterType type)
{
  return
       type == KalmanFilterExperimentParameterType::initial_state_estimate
    || type == KalmanFilterExperimentParameterType::initial_state_real
    || type == KalmanFilterExperimentParameterType::real_measurement_noise
    || type == KalmanFilterExperimentParameterType::real_process_noise
    || type == KalmanFilterExperimentParameterType::input
    || type == KalmanFilterExperimentParameterType::state_names;
}

void KalmanFilterExperimentParameter::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started KalmanFilterExperimentParameter::Test");
  assert(IsMatrix(KalmanFilterExperimentParameterType::control));
  assert(IsMatrix(KalmanFilterExperimentParameterType::estimated_measurement_noise));
  assert(IsMatrix(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain));
  assert(IsMatrix(KalmanFilterExperimentParameterType::estimated_process_noise_covariance));
  assert(IsMatrix(KalmanFilterExperimentParameterType::initial_covariance_estimate));
  assert(IsVector(KalmanFilterExperimentParameterType::initial_state_estimate));
  assert(IsVector(KalmanFilterExperimentParameterType::initial_state_real));
  assert(IsVector(KalmanFilterExperimentParameterType::input));
  assert(IsVector(KalmanFilterExperimentParameterType::real_measurement_noise));
  assert(IsVector(KalmanFilterExperimentParameterType::real_process_noise));
  assert(IsMatrix(KalmanFilterExperimentParameterType::observation));
  assert(IsVector(KalmanFilterExperimentParameterType::state_names));
  assert(IsMatrix(KalmanFilterExperimentParameterType::state_transition));
  TRACE("Finished KalmanFilterExperimentParameter::Test");
}
const std::string KalmanFilterExperimentParameter::ToDescription(const KalmanFilterExperimentParameterType type)
{
  //Check for the subset
  if (CanConvertToKalmanFilterParameter(type))
  {
    const KalmanFilterParameterType sub_type = ConvertToKalmanFilterParameter(type);
    return KalmanFilterParameter::ToDescription(sub_type);
  }
  if (CanConvertToWhiteNoiseSystemParameter(type))
  {
    const WhiteNoiseSystemParameterType sub_type = ConvertToWhiteNoiseSystemParameter(type);
    return WhiteNoiseSystemParameter::ToDescription(sub_type);
  }
  //Check the unique types
  switch (type)
  {
    case KalmanFilterExperimentParameterType::input:
      return std::string("Vector of inputs");
    case KalmanFilterExperimentParameterType::state_names:
      return std::string("Vector of the state element names");
    default: assert(!"Unimplemented type of KalmanFilterExperimentParameterType");
      throw std::logic_error(__func__);
  }
}

const std::string KalmanFilterExperimentParameter::ToName(const KalmanFilterExperimentParameterType type)
{
  //Check for the subset
  if (CanConvertToKalmanFilterParameter(type))
  {
    const KalmanFilterParameterType sub_type = ConvertToKalmanFilterParameter(type);
    return KalmanFilterParameter::ToName(sub_type);
  }
  if (CanConvertToWhiteNoiseSystemParameter(type))
  {
    const WhiteNoiseSystemParameterType sub_type = ConvertToWhiteNoiseSystemParameter(type);
    return WhiteNoiseSystemParameter::ToName(sub_type);
  }
  //Check the unique types
  switch (type)
  {
    case KalmanFilterExperimentParameterType::input:
      return std::string("Input");
    case KalmanFilterExperimentParameterType::state_names:
      return std::string("State names");
    default: assert(!"Unimplemented type of KalmanFilterExperimentParameterType");
      throw std::logic_error(__func__);
  }
}

const std::string KalmanFilterExperimentParameter::ToSymbol(const KalmanFilterExperimentParameterType type)
{
  //Check for the subset
  if (CanConvertToKalmanFilterParameter(type))
  {
    const KalmanFilterParameterType sub_type = ConvertToKalmanFilterParameter(type);
    return KalmanFilterParameter::ToSymbol(sub_type);
  }
  if (CanConvertToWhiteNoiseSystemParameter(type))
  {
    const WhiteNoiseSystemParameterType sub_type = ConvertToWhiteNoiseSystemParameter(type);
    return WhiteNoiseSystemParameter::ToSymbol(sub_type);
  }
  //Check the unique types
  switch (type)
  {
    case KalmanFilterExperimentParameterType::input:
      return std::string("y");
    case KalmanFilterExperimentParameterType::state_names:
      return std::string(""); //State names has no symbol
    default: assert(!"Unimplemented type of KalmanFilterExperimentParameterType");
      throw std::logic_error(__func__);
  }
}
