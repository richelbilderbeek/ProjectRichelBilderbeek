#ifndef QTDASWAHRESCHLAGERFESTCANVAS_H
#define QTDASWAHRESCHLAGERFESTCANVAS_H

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct DasWahreSchlagerfestWidget;

struct QtDasWahreSchlagerfestCanvas : public QtCanvas
{
  QtDasWahreSchlagerfestCanvas();

  void keyPressEvent(QKeyEvent *e);

  private:
  const boost::shared_ptr<DasWahreSchlagerfestWidget> m_widget;

  static const boost::shared_ptr<DasWahreSchlagerfestWidget> CreateWidget() noexcept;
};

} //~namespace ribi

#endif // QTDASWAHRESCHLAGERFESTCANVAS_H
