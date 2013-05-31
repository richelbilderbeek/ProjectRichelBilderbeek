#ifndef WHITENOISESYSTEMPARAMETER_H
#define WHITENOISESYSTEMPARAMETER_H

#include <string>
#include <vector>
#include "whitenoisesystemparametertype.h"

///A single WhiteNoiseSystemParameter
///for example, the state transition matrix
/// - is a matrix
/// - is not a vector
/// - has a description like 'Matrix that [...]'
/// - has the name 'State transition matrix'
/// - has the symbol 'A'
struct WhiteNoiseSystemParameter
{
  ///Obtain all WhiteNoiseSystemParameterType values, except n_parameters
  static const std::vector<WhiteNoiseSystemParameterType> GetAll();

  ///Is the type a matrix?
  static bool IsMatrix(const WhiteNoiseSystemParameterType type);

  ///Is the type a vector?
  static bool IsVector(const WhiteNoiseSystemParameterType type);

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  static const std::string ToDescription(const WhiteNoiseSystemParameterType type);

  ///Obtain the full name of a type, e.g. 'State transition'
  static const std::string ToName(const WhiteNoiseSystemParameterType type);

  ///Obtain the symbol of a type, e.g. 'A'
  static const std::string ToSymbol(const WhiteNoiseSystemParameterType type);
};

#endif // WHITENOISESYSTEMPARAMETER_H
