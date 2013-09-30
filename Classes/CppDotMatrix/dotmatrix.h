#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include <string>
#include <vector>
#include <boost/array.hpp>

namespace ribi {

struct DotMatrix
{
  ///Obtain a y-x ordered matrix of a character
  ///Returns a matrix with zeroes of the character is not found
  ///Dot-matrix characters are
  ///size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
  ///size 6 (width) x 8 (height) pixels, including empty spacer pixels
  static const boost::array<boost::array<int,5> ,7> Get(const char c) noexcept;
};

} //~namespace ribi

#endif // DOTMATRIX_H
