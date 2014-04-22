#ifndef TRIBOOL_H
#define TRIBOOL_H

namespace ribi {

///Class similar to Boost.Tribool,
///except that this version does not surprise me as often
enum class Tribool { True, False, Indeterminate };

} //~namespace ribi

#endif // TRIBOOL_H
