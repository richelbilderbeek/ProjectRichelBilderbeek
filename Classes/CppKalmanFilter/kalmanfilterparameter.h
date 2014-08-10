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
  KalmanFilterParameter();

  ///Obtain all KalmanFilterParameterType values, except n_parameters
  std::vector<KalmanFilterParameterType> GetAll() const noexcept;

  ///Is the type a matrix?
  bool IsMatrix(const KalmanFilterParameterType type) const noexcept;

  ///Is the type a vector?
  bool IsVector(const KalmanFilterParameterType type) const noexcept;

  ///Obtain the full name of a type, e.g. 'Matrix to capture the physics of the system'
  std::string ToDescription(const KalmanFilterParameterType type) const noexcept;

  ///Obtain the full name of a type, e.g. 'State transition'
  std::string ToName(const KalmanFilterParameterType type) const noexcept;

  ///Obtain the symbol of a type, e.g. 'A'
  std::string ToSymbol(const KalmanFilterParameterType type) const noexcept;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERPARAMETER_H
