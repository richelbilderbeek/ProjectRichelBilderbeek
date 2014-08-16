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
  WhiteNoiseSystemParameter();

  ///Obtain all WhiteNoiseSystemParameterType values, except n_parameters
  std::vector<WhiteNoiseSystemParameterType> GetAll() const noexcept;

  ///Is the type a matrix?
  bool IsMatrix(const WhiteNoiseSystemParameterType type) const noexcept;

  ///Is the type a vector?
  bool IsVector(const WhiteNoiseSystemParameterType type) const noexcept;

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  std::string ToDescription(const WhiteNoiseSystemParameterType type) const noexcept;

  ///Obtain the full name of a type, e.g. 'State transition'
  std::string ToName(const WhiteNoiseSystemParameterType type) const noexcept;

  ///Obtain the symbol of a type, e.g. 'A'
  std::string ToSymbol(const WhiteNoiseSystemParameterType type) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // WHITENOISESYSTEMPARAMETER_H
