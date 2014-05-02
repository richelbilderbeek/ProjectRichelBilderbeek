#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "whitenoisesystemparametertype.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

bool ribi::kalman::operator<(const WhiteNoiseSystemParameterType lhs, const WhiteNoiseSystemParameterType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) < static_cast<int>(rhs);
}

bool ribi::kalman::operator==(const WhiteNoiseSystemParameterType lhs, const WhiteNoiseSystemParameterType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) == static_cast<int>(rhs);
}

bool ribi::kalman::operator!=(const WhiteNoiseSystemParameterType lhs, const WhiteNoiseSystemParameterType rhs)
{
  return !(lhs == rhs);
}
