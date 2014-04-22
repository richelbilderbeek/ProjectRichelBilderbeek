#ifndef QTDOTMATRIXSTRING_H
#define QTDOTMATRIXSTRING_H

/*

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
//#include <QPixmap>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct DotMatrixString;

///QtDotMatrix creates a dot matrix QImage of a character
struct QtDotMatrixString
{
  QtDotMatrixString(const std::string& s, const int spacing);

  ///Read back the dot matrix info
  const boost::shared_ptr<const DotMatrixString> GetMatrix() const noexcept { return m_matrix; }

  ///Create a QImage from the character
  const boost::shared_ptr<QImage> CreateImage() const noexcept;

  private:
  const boost::shared_ptr<DotMatrixString> m_matrix;
};

} //~namespace ribi
*/

#endif // QTDOTMATRIXSTRING_H
