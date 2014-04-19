#ifndef QTSIMMYSTERYMACHINECANVAS_H
#define QTSIMMYSTERYMACHINECANVAS_H

#include "qtcanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct MysteryMachineWidget;

struct QtMysteryMachineCanvas : public QtCanvas
{
  QtMysteryMachineCanvas();

  void keyPressEvent(QKeyEvent *e);

  private:
  const boost::shared_ptr<MysteryMachineWidget> m_widget;

  static const boost::shared_ptr<Canvas> CreateCanvas(const int width, const int height) noexcept;
  static const boost::shared_ptr<MysteryMachineWidget> CreateWidget() noexcept;

  void OnChanged();
};

} //~namespace ribi

#endif // QTSIMMYSTERYMACHINECANVAS_H
