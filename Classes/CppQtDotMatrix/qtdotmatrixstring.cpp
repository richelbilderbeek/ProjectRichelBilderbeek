
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdotmatrixstring.h"

#include <cassert>

#include <QPainter>
#include <QPixmap>

#include "dotmatrixstring.h"
#pragma GCC diagnostic pop

ribi::QtDotMatrixString::QtDotMatrixString(const std::string& s,
  const int spacing)
  : m_matrix(new DotMatrixString(s,spacing))
{
  assert(m_matrix);
}

const QPixmap ribi::QtDotMatrixString::CreatePixmap() const
{
  const int height = this->m_matrix->GetMatrixHeight();
  const int width = this->m_matrix->GetMatrixWidth();
  QPixmap pixmap(width,height);

  QPainter painter(&pixmap);

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const bool b = m_matrix->GetMatrix(x,y);
      const QColor color = b ? Qt::black : Qt::white;
      painter.setPen(color);
      painter.drawPoint(x,y);
    }
  }
  return pixmap;
}
