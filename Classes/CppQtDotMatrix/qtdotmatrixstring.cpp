/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdotmatrixstring.h"

#include <cassert>


#include <QImage>
#include <QRgb>

#include "dotmatrixstring.h"
#pragma GCC diagnostic pop

ribi::QtDotMatrixString::QtDotMatrixString(const std::string& s,
  const int spacing)
  : m_matrix(new DotMatrixString(s,spacing))
{
  assert(m_matrix);
}

const boost::shared_ptr<QImage> ribi::QtDotMatrixString::CreateImage() const noexcept
{
  return m_matrix->CreateImage();
}

*/
