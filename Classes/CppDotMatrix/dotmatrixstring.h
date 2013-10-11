#ifndef DOTMATRIXSTRING_H
#define DOTMATRIXSTRING_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct DotMatrixChar;

///DotMatrixString creates a dot matrix 2D array of a string
struct DotMatrixString
{
  ///Give it a std::string and a spacing (number of pixels) between the characters
  DotMatrixString(const std::string& s, const int spacing);

  ///Read back the string
  const std::string GetString() const noexcept;

  ///Read if the coordinat is black/high or white/low
  bool GetMatrix(const int x, const int y) const;

  ///Get the matrix height
  int GetMatrixHeight() const noexcept;

  ///Get the matrix width
  int GetMatrixWidth() const noexcept;

  private:
  const int m_spacing;
  const std::vector<boost::shared_ptr<const DotMatrixChar> > m_v;

  static const std::vector<boost::shared_ptr<const DotMatrixChar> >
    CreateDotMatrixChars(const std::string& s);
};

std::ostream& operator<<(std::ostream& os, const DotMatrixString& m);

} //~namespace ribi

#endif // DOTMATRIXSTRING_H
