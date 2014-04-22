#ifndef KALMANFILTEREXPERIMENTPARAMETER_H
#define KALMANFILTEREXPERIMENTPARAMETER_H

#include <map>
#include <string>

#include "kalmanfilterparametertype.h"
#include "kalmanfilterexperimentparametertype.h"
#include "whitenoisesystemparametertype.h"

namespace ribi {
namespace kalman {

///A parameter used in a KalmanFilterExperiment
///Note that a KalmanFilterExperiment uses a KalmanFilter,
///which has its own parameter type called KalmanFilterParameter, which is
///a subset of these
struct KalmanFilterExperimentParameter
{
  ///Check if a convert from KalmanFilterExperimentParameter to a KalmanFilterParameter will succeed
  static bool CanConvertToKalmanFilterParameter(const KalmanFilterExperimentParameterType parameter) noexcept;

  ///Check if a convert from KalmanFilterExperimentParameter to a WhiteNoiseSystemParameter will succeed
  static bool CanConvertToWhiteNoiseSystemParameter(const KalmanFilterExperimentParameterType parameter) noexcept;

  ///Convert a KalmanFilterParameter to a KalmanFilterExperimentParameter,
  ///which will always succeed
  static KalmanFilterExperimentParameterType ConvertToKalmanFilterExperimentParameter(const KalmanFilterParameterType parameter) noexcept;

  ///Convert a KalmanFilterParameter to a KalmanFilterExperimentParameter,
  ///which will always succeed
  static KalmanFilterExperimentParameterType ConvertToKalmanFilterExperimentParameter(const WhiteNoiseSystemParameterType parameter) noexcept;

  ///Convert a KalmanFilterExperimentParameter to a KalmanFilterParameter,
  ///assumes CanConvertToKalmanFilterParameter succeeds
  static KalmanFilterParameterType ConvertToKalmanFilterParameter(const KalmanFilterExperimentParameterType parameter) noexcept;

  ///Convert a KalmanFilterExperimentParameter to a WhiteNoiseSystemParameterType,
  ///assumes CanConvertToWhiteNoiseSystemParameter succeeds
  static WhiteNoiseSystemParameterType ConvertToWhiteNoiseSystemParameter(const KalmanFilterExperimentParameterType parameter) noexcept;

  ///Get all KalmanFilterExperimentParameterType values
  static std::vector<KalmanFilterExperimentParameterType> GetAll() noexcept;

  ///Is this parameter a matrix/vector of type double?
  static bool IsDouble(const KalmanFilterExperimentParameterType type);

  ///Is this parameter a matrix/vector of type std::string for a function?
  static bool IsFunction(const KalmanFilterExperimentParameterType type);

  ///Is this parameter a matrix/vector of type integer?
  static bool IsInt(const KalmanFilterExperimentParameterType type);

  ///Is this parameter a matrix/vector of type std::string?
  static bool IsString(const KalmanFilterExperimentParameterType type);

  ///Is this parameter a matrix?
  static bool IsMatrix(const KalmanFilterExperimentParameterType type);

  ///Is this parameter a vector?
  static bool IsVector(const KalmanFilterExperimentParameterType type);

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  static std::string ToDescription(const KalmanFilterExperimentParameterType type) noexcept;

  ///Obtain the full name of a type, e.g. 'State transition'
  static std::string ToName(const KalmanFilterExperimentParameterType type) noexcept;

  ///Obtain the symbol of a type, e.g. 'A'
  static std::string ToSymbol(const KalmanFilterExperimentParameterType type) noexcept;

  private:

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  static const std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> > m_map_kalman_filter;
  static const std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> > m_map_white_noise_system;
  static const std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> > CreateMapKalmanFilter();
  static const std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> > CreateMapWhiteNoiseSystem();
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTEREXPERIMENTPARAMETER_H
