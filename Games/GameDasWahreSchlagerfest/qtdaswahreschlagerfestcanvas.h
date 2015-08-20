#ifndef QTDASWAHRESCHLAGERFESTCANVAS_H
#define QTDASWAHRESCHLAGERFESTCANVAS_H

#include "qtcanvas.h"
#include "qtdaswahreschlagerfestwidget.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct DasWahreSchlagerfestWidget;

struct QtDasWahreSchlagerfestCanvas : public QtCanvas, public ribi::DasWahreSchlagerfestDisplay
{
  QtDasWahreSchlagerfestCanvas(const int width = 9, const int height = 5);

  void Display(const DasWahreSchlagerfestWidget& widget) override;
  void OnChanged(const DasWahreSchlagerfestWidget& widget) override;
  void keyPressEvent(QKeyEvent *e);

  private:
  //QtDasWahreSchlagerfestWidget m_widget;
  DasWahreSchlagerfestWidget m_game;
};

} //~namespace ribi

#endif // QTDASWAHRESCHLAGERFESTCANVAS_H
