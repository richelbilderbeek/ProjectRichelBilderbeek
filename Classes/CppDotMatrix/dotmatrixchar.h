#ifndef RIBI_DOTMATRIXCHAR_H
#define RIBI_DOTMATRIXCHAR_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/array.hpp>
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

///DotMatrixChar creates a dot matrix 2D array of a character
struct DotMatrixChar
{
  DotMatrixChar(const char c);

  boost::shared_ptr<QImage> CreateImage() const noexcept;

  ///Read back the character
  char GetChar() const noexcept { return m_c; }

  ///Read if the coordinat is black/high or white/low
  bool GetMatrix(const int x, const int y) const;

  ///Get the matrix height
  int GetMatrixHeight() const noexcept { return 7; }

  ///Get the matrix width
  int GetMatrixWidth() const noexcept { return 5; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ~DotMatrixChar() noexcept {}
  friend void boost::checked_delete<>(DotMatrixChar* x);
  friend void boost::checked_delete<>(const DotMatrixChar* x);
  ///The character
  const char m_c;

  ///The character matrix
  const boost::array<boost::array<int,5> ,7> m_matrix;

  ///Obtain a y-x ordered matrix of a character
  ///Returns a matrix with zeroes of the character is not found
  ///Dot-matrix characters are
  ///size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
  ///size 6 (width) x 8 (height) pixels, including empty spacer pixels
  static boost::array<boost::array<int,5> ,7> GetChar(const char c) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const DotMatrixChar& m);

} //~namespace ribi

#endif // RIBI_DOTMATRIXCHAR_H
