#ifndef WHITENOISESYSTEMPARAMETER_H
#define WHITENOISESYSTEMPARAMETER_H

#include <string>
#include <vector>
#include "whitenoisesystemparametertype.h"

namespace ribi {
namespace kalman {

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
  static std::vector<WhiteNoiseSystemParameterType> GetAll() noexcept;

  ///Is the type a matrix?
  static bool IsMatrix(const WhiteNoiseSystemParameterType type) noexcept;

  ///Is the type a vector?
  static bool IsVector(const WhiteNoiseSystemParameterType type) noexcept;

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  static std::string ToDescription(const WhiteNoiseSystemParameterType type) noexcept;

  ///Obtain the full name of a type, e.g. 'State transition'
  static std::string ToName(const WhiteNoiseSystemParameterType type) noexcept;

  ///Obtain the symbol of a type, e.g. 'A'
  static std::string ToSymbol(const WhiteNoiseSystemParameterType type) noexcept;
};

} //~namespace kalman
} //~namespace ribi

#endif // WHITENOISESYSTEMPARAMETER_H
