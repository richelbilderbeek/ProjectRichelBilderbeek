#ifndef WHITENOISESYSTEMTYPE_H
#define WHITENOISESYSTEMTYPE_H

#include <string>

namespace ribi {
namespace kalman {

enum class WhiteNoiseSystemType
{
  gaps_filled,
  lagged,
  standard,
  n_types
};

bool operator==(const WhiteNoiseSystemType lhs, const WhiteNoiseSystemType rhs);
bool operator!=(const WhiteNoiseSystemType lhs, const WhiteNoiseSystemType rhs);
bool operator<(const WhiteNoiseSystemType lhs, const WhiteNoiseSystemType rhs);

} //~namespace kalman
} //~namespace ribi

#endif // WHITENOISESYSTEMTYPE_H
