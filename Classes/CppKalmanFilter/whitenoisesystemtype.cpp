

#include "whitenoisesystemtype.h"

bool ribi::kalman::operator==(const WhiteNoiseSystemType lhs, const WhiteNoiseSystemType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) == static_cast<int>(rhs);
}

bool ribi::kalman::operator!=(const WhiteNoiseSystemType lhs, const WhiteNoiseSystemType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) != static_cast<int>(rhs);
}

bool ribi::kalman::operator<(const WhiteNoiseSystemType lhs, const WhiteNoiseSystemType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) < static_cast<int>(rhs);
}
