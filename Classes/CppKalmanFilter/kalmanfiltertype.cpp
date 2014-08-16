#include "kalmanfiltertype.h"

#include <cassert>
#include <stdexcept>

bool ribi::kalman::operator==(const KalmanFilterType lhs, const KalmanFilterType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) == static_cast<int>(rhs);
}

bool ribi::kalman::operator!=(const KalmanFilterType lhs, const KalmanFilterType rhs)
{
  return !(lhs == rhs);
}

bool ribi::kalman::operator<(const KalmanFilterType lhs, const KalmanFilterType rhs)
{
  //Must cast enum class to integer, because of a bug
  //in GCC version 4.4.0:
  //http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
  return static_cast<int>(lhs) < static_cast<int>(rhs);
}
