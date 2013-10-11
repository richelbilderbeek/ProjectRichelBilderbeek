#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdotmatrixchar.h"

#include <cassert>

#include <QPainter>
#include <QPixmap>

#include "dotmatrixchar.h"
#pragma GCC diagnostic pop

ribi::QtDotMatrixChar::QtDotMatrixChar(const char c)
  : m_matrix(new DotMatrixChar(c))
{
  assert(m_matrix);
}

const QPixmap ribi::QtDotMatrixChar::CreatePixmap() const
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
