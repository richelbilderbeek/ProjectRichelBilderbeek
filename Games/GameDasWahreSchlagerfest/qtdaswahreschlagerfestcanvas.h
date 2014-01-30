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
  QtDasWahreSchlagerfestCanvas(const int width = 9, const int height = 5);

  void keyPressEvent(QKeyEvent *e);

  private:
  const boost::shared_ptr<DasWahreSchlagerfestWidget> m_widget;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<DasWahreSchlagerfestWidget> CreateWidget(const int width, const int height) noexcept;

  void OnChanged();
};

} //~namespace ribi

#endif // QTDASWAHRESCHLAGERFESTCANVAS_H
