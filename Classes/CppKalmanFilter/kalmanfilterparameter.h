#ifndef KALMANFILTERPARAMETER_H
#define KALMANFILTERPARAMETER_H

#include <string>
#include "kalmanfilterparametertype.h"

namespace ribi {
namespace kalman {

///A single KalmanFilterParameter
///for example, the state transition matrix
/// - is a matrix
/// - is not a vector
/// - has a description like 'Matrix that [...]'
/// - has the name 'State transition matrix'
/// - has the symbol 'A'
struct KalmanFilterParameter
{
  ///Obtain all KalmanFilterParameterType values, except n_parameters
  static std::vector<KalmanFilterParameterType> GetAll() noexcept;

  ///Is the type a matrix?
  static bool IsMatrix(const KalmanFilterParameterType type) noexcept;

  ///Is the type a vector?
  static bool IsVector(const KalmanFilterParameterType type) noexcept;

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  static std::string ToDescription(const KalmanFilterParameterType type) noexcept;

  ///Obtain the full name of a type, e.g. 'State transition'
  static std::string ToName(const KalmanFilterParameterType type) noexcept;

  ///Obtain the symbol of a type, e.g. 'A'
  static std::string ToSymbol(const KalmanFilterParameterType type) noexcept;
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERPARAMETER_H
