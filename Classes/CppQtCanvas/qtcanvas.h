#ifndef QTCANVAS_H
#define QTCANVAS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <QWidget>
#include "canvas.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Canvas;

///A Canvas class that can be used on a QDialog
///If the Canvas is modified, this is displayed in the QtCanvas
struct QtCanvas : public QWidget
{
  Canvas m_canvas;
};

} //~namespace ribi

#endif // QTCANVAS_H
