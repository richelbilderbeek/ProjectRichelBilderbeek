#ifndef QTDOTMATRIX_H
#define QTDOTMATRIX_H

/*

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct DotMatrixChar;

///QtDotMatrix creates a dot matrix QImage of a characters
struct QtDotMatrixChar
{
  QtDotMatrixChar(const char c);

  ///Read back the dot matrix info
  const boost::shared_ptr<const DotMatrixChar> GetMatrix() const noexcept { return m_matrix; }

  ///Create a QPixmap from the character
  const boost::shared_ptr<QImage> CreateImage() const noexcept;

  private:
  const boost::shared_ptr<DotMatrixChar> m_matrix;
};

} //~namespace ribi

*/

#endif // QTDOTMATRIX_H
