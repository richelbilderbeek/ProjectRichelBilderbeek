#ifndef QTMAZIAKCANVAS_H
#define QTMAZIAKCANVAS_H

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

struct MaziakMainDialog;

struct QtMaziakCanvas : public QtCanvas
{
  QtMaziakCanvas(const int width = 9, const int height = 5);

  void keyPressEvent(QKeyEvent *e);

  private:
  const boost::shared_ptr<MaziakMainDialog> m_widget;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<MaziakMainDialog> CreateWidget(const int width, const int height) noexcept;

  void OnChanged();
};

} //~namespace maziak
} //~namespace ribi


#endif // QTMAZIAKCANVAS_H
