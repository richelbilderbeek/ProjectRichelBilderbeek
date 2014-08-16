#ifndef RIBI_CHESSHELPER_H
#define RIBI_CHESSHELPER_H

#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Help adding constness a bit
template <class T>
const std::vector<boost::shared_ptr<const T>> AddConst(
  const std::vector<boost::shared_ptr<T>> v)
{
  return std::vector<boost::shared_ptr<const T>>(v.begin(),v.end());
}

///Help adding constness a bit
template <class T>
const std::set<boost::shared_ptr<const T>> AddConst(
  const std::set<boost::shared_ptr<T>> v)
{
  return std::set<boost::shared_ptr<const T>>(v.begin(),v.end());
}

} //~namespace ribi

#endif // RIBI_CHESSHELPER_H
