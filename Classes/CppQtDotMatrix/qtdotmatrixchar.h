#ifndef QTDOTMATRIX_H
#define QTDOTMATRIX_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QPixmap>
#pragma GCC diagnostic pop


namespace ribi {

struct DotMatrixChar;

///QtDotMatrix creates a dot matrix QPixmap of a character
struct QtDotMatrixChar
{
  QtDotMatrixChar(const char c);

  ///Read back the dot matrix info
  const boost::shared_ptr<const DotMatrixChar> GetMatrix() const noexcept { return m_matrix; }

  ///Create a QPixmap from the character
  const QPixmap CreatePixmap() const;

  private:
  const boost::shared_ptr<DotMatrixChar> m_matrix;
};

} //~namespace ribi

#endif // QTDOTMATRIX_H
