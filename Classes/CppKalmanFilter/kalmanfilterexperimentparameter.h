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
  static bool CanConvertToKalmanFilterParameter(const KalmanFilterExperimentParameterType parameter);

  ///Check if a convert from KalmanFilterExperimentParameter to a WhiteNoiseSystemParameter will succeed
  static bool CanConvertToWhiteNoiseSystemParameter(const KalmanFilterExperimentParameterType parameter);

  ///Convert a KalmanFilterParameter to a KalmanFilterExperimentParameter,
  ///which will always succeed
  static KalmanFilterExperimentParameterType ConvertToKalmanFilterExperimentParameter(const KalmanFilterParameterType parameter);

  ///Convert a KalmanFilterParameter to a KalmanFilterExperimentParameter,
  ///which will always succeed
  static KalmanFilterExperimentParameterType ConvertToKalmanFilterExperimentParameter(const WhiteNoiseSystemParameterType parameter);

  ///Convert a KalmanFilterExperimentParameter to a KalmanFilterParameter,
  ///assumes CanConvertToKalmanFilterParameter succeeds
  static KalmanFilterParameterType ConvertToKalmanFilterParameter(const KalmanFilterExperimentParameterType parameter);

  ///Convert a KalmanFilterExperimentParameter to a WhiteNoiseSystemParameterType,
  ///assumes CanConvertToWhiteNoiseSystemParameter succeeds
  static WhiteNoiseSystemParameterType ConvertToWhiteNoiseSystemParameter(const KalmanFilterExperimentParameterType parameter);

  ///Get all KalmanFilterExperimentParameterType values
  static const std::vector<KalmanFilterExperimentParameterType> GetAll();

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

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  static const std::string ToDescription(const KalmanFilterExperimentParameterType type);

  ///Obtain the full name of a type, e.g. 'State transition'
  static const std::string ToName(const KalmanFilterExperimentParameterType type);

  ///Obtain the symbol of a type, e.g. 'A'
  static const std::string ToSymbol(const KalmanFilterExperimentParameterType type);

  private:
  static const std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> > m_map_kalman_filter;
  static const std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> > m_map_white_noise_system;
  static const std::vector<std::pair<KalmanFilterParameterType,KalmanFilterExperimentParameterType> > CreateMapKalmanFilter();
  static const std::vector<std::pair<WhiteNoiseSystemParameterType,KalmanFilterExperimentParameterType> > CreateMapWhiteNoiseSystem();
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTEREXPERIMENTPARAMETER_H
