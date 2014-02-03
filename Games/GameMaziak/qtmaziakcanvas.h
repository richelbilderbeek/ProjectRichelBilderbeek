#ifndef QTMAZIAKCANVAS_H
#define QTMAZIAKCANVAS_H

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

struct MainDialog;

struct QtMaziakCanvas : public QtCanvas
{
  QtMaziakCanvas(const int size);

  void keyPressEvent(QKeyEvent *e);

  private:
  const boost::shared_ptr<MainDialog> m_widget;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<MainDialog> CreateWidget(const int size) noexcept;

  void OnChanged();
};

} //~namespace maziak
} //~namespace ribi


#endif // QTMAZIAKCANVAS_H
