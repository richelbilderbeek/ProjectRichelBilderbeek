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
  KalmanFilterExperimentParameter();

  ///Check if a convert from KalmanFilterExperimentParameter to a KalmanFilterParameter will succeed
  bool CanConvertToKalmanFilterParameter(const KalmanFilterExperimentParameterType parameter) const noexcept;

  ///Check if a convert from KalmanFilterExperimentParameter to a WhiteNoiseSystemParameter will succeed
  bool CanConvertToWhiteNoiseSystemParameter(const KalmanFilterExperimentParameterType parameter) const noexcept;

  ///Convert a KalmanFilterParameter to a KalmanFilterExperimentParameter,
  ///which will always succeed
  KalmanFilterExperimentParameterType ConvertToKalmanFilterExperimentParameter(const KalmanFilterParameterType parameter) const noexcept;

  ///Convert a KalmanFilterParameter to a KalmanFilterExperimentParameter,
  ///which will always succeed
  KalmanFilterExperimentParameterType ConvertToKalmanFilterExperimentParameter(const WhiteNoiseSystemParameterType parameter) const noexcept;

  ///Convert a KalmanFilterExperimentParameter to a KalmanFilterParameter,
  ///assumes CanConvertToKalmanFilterParameter succeeds
  KalmanFilterParameterType ConvertToKalmanFilterParameter(const KalmanFilterExperimentParameterType parameter) const noexcept;

  ///Convert a KalmanFilterExperimentParameter to a WhiteNoiseSystemParameterType,
  ///assumes CanConvertToWhiteNoiseSystemParameter succeeds
  WhiteNoiseSystemParameterType ConvertToWhiteNoiseSystemParameter(const KalmanFilterExperimentParameterType parameter) const noexcept;

  ///Get all KalmanFilterExperimentParameterType values
  std::vector<KalmanFilterExperimentParameterType> GetAll() const noexcept;

  ///Is this parameter a matrix/vector of type double?
  bool IsDouble(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Is this parameter a matrix/vector of type std::string for a function?
  bool IsFunction(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Is this parameter a matrix/vector of type integer?
  bool IsInt(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Is this parameter a matrix/vector of type std::string?
  bool IsString(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Is this parameter a matrix?
  bool IsMatrix(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Is this parameter a vector?
  bool IsVector(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  std::string ToDescription(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Obtain the full name of a type, e.g. 'State transition'
  std::string ToName(const KalmanFilterExperimentParameterType type) const noexcept;

  ///Obtain the symbol of a type, e.g. 'A'
  std::string ToSymbol(const KalmanFilterExperimentParameterType type) const noexcept;

  private:

  #ifndef NDEBUG
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
