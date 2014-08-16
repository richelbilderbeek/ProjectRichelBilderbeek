#ifndef RIBI_QTCANVASDIALOG_H
#define RIBI_QTCANVASDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop


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
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void resizeEvent(QResizeEvent *) override;

  private:
  ~QtCanvasDialog() noexcept;
  friend void boost::checked_delete<>(QtCanvasDialog* x);
  friend void boost::checked_delete<>(const QtCanvasDialog* x);
  friend class boost::detail::sp_ms_deleter<QtCanvasDialog>;
  friend class boost::detail::sp_ms_deleter<const QtCanvasDialog>;

  QtCanvas * const m_qtcanvas;

  void OnQtCanvasDestroy();
};

} //~namespace ribi

#endif // RIBI_QTCANVASDIALOG_H
