#ifndef QTCANVASDIALOG_H
#define QTCANVASDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#pragma GCC diagnostic pop

#include "qthideandshowdialog.h"

namespace ribi {

struct QtCanvas;

///QtCanvasDialog makes QtCanvas displayable as a modal dialog
class QtCanvasDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  ///qtcanvas will be deleted when this object goes out of scope!
  QtCanvasDialog(QtCanvas * const qtcanvas);
  QtCanvasDialog(const QtCanvasDialog&) = delete;
  QtCanvasDialog& operator=(const QtCanvasDialog&) = delete;

  protected:
  void keyPressEvent(QKeyEvent *event);
  void resizeEvent(QResizeEvent *);

  private:
  ~QtCanvasDialog() noexcept;
  friend void boost::checked_delete<>(QtCanvasDialog* x);
  friend void boost::checked_delete<>(const QtCanvasDialog* x);

  QtCanvas * const m_qtcanvas;

  void OnQtCanvasDestroy();
};

} //~namespace ribi

#endif // QTCANVASDIALOG_H
