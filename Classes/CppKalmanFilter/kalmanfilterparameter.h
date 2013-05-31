#ifndef KALMANFILTERPARAMETER_H
#define KALMANFILTERPARAMETER_H

#include <string>
#include "kalmanfilterparametertype.h"

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
  static const std::vector<KalmanFilterParameterType> GetAll();

  ///Is the type a matrix?
  static bool IsMatrix(const KalmanFilterParameterType type);

  ///Is the type a vector?
  static bool IsVector(const KalmanFilterParameterType type);

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  static const std::string ToDescription(const KalmanFilterParameterType type);

  ///Obtain the full name of a type, e.g. 'State transition'
  static const std::string ToName(const KalmanFilterParameterType type);

  ///Obtain the symbol of a type, e.g. 'A'
  static const std::string ToSymbol(const KalmanFilterParameterType type);
};

#endif // KALMANFILTERPARAMETER_H
