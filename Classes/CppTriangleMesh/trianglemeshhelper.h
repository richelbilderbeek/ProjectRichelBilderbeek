#ifndef TRIANGLEMESHHELPER_H
#define TRIANGLEMESHHELPER_H

#include <algorithm>
#include <cassert>
#include <map>
#include <set>
#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "constcoordinat2d.h"
#include "coordinat3d.h"

#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Help adding constness a bit
template <class T>
const std::vector<boost::shared_ptr<const T> > AddConst(
  const std::vector<boost::shared_ptr<T> > v)
{
  return std::vector<boost::shared_ptr<const T> >(v.begin(),v.end());
}

//From http://www.richelbilderbeek.nl/CppCanLexicalCast.htm
template <class TargetType>
bool CanLexicalCast(const std::string& from)
{
  try
  {
    boost::lexical_cast<TargetType>(from);
  }
  catch (boost::bad_lexical_cast&)
  {
    return false;
  }
  catch (...)
  {
    assert(!"Something unexpected happened");
    throw;
  }
  return true;
}
const std::string formatDigitsBehindTheComma(const double x, const int n);

double DotProduct(const ribi::Coordinat3D& v1,const ribi::Coordinat3D& v2);

const ribi::Coordinat3D vOut(
  const ribi::Coordinat3D& v1,
  const ribi::Coordinat3D& v2);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHHELPER_H
