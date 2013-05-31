#ifndef CHESSHELPER_H
#define CHESSHELPER_H

#include <boost/shared_ptr.hpp>
#include <set>
#include <vector>

///Help adding constness a bit
template <class T>
const std::vector<boost::shared_ptr<const T> > AddConst(
  const std::vector<boost::shared_ptr<T> > v)
{
  return std::vector<boost::shared_ptr<const T> >(v.begin(),v.end());
}

///Help adding constness a bit
template <class T>
const std::set<boost::shared_ptr<const T> > AddConst(
  const std::set<boost::shared_ptr<T> > v)
{
  return std::set<boost::shared_ptr<const T> >(v.begin(),v.end());
}

#endif // CHESSHELPER_H
