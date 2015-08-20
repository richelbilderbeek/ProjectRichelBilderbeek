#ifndef QTDASWAHRESCHLAGERFESTCANVAS_H
#define QTDASWAHRESCHLAGERFESTCANVAS_H

/*

#include "qtcanvas.h"
#include "qtdaswahreschlagerfestwidget.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct DasWahreSchlagerfestWidget;

class QtDasWahreSchlagerfestCanvas : public QWidget, public ribi::DasWahreSchlagerfestDisplay
{
  Q_OBJECT

public:

  QtDasWahreSchlagerfestCanvas(const int width = 9, const int height = 5, QWidget *parent = 0);

  void Display(const DasWahreSchlagerfestWidget& widget) override;
  void keyPressEvent(QKeyEvent *e);
  void OnChanged(const DasWahreSchlagerfestWidget& widget) override;
  void paintEvent(QPaintEvent *);

  private:
  //QtDasWahreSchlagerfestWidget m_widget;
  DasWahreSchlagerfestWidget m_game;
};

} //~namespace ribi

*/

#endif // QTDASWAHRESCHLAGERFESTCANVAS_H
