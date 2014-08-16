#ifndef TRIBOOL_H
#define TRIBOOL_H

#include <iosfwd>

namespace ribi {

///Class similar to Boost.Tribool,
///except that this version does not surprise me as often
enum class Tribool { True, False, Indeterminate };

std::ostream& operator<<(std::ostream& os, const Tribool tribool);

} //~namespace ribi

#endif // TRIBOOL_H
