#ifndef RIBI_QTCANVAS_H
#define RIBI_QTCANVAS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#include <QPlainTextEdit>
#include "canvas.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Canvas;

///A Canvas class that can be used on a QDialog
///If the Canvas is modified, this is displayed in the QtCanvas
class QtCanvas : public QWidget
{
  Q_OBJECT

public:

  QtCanvas(const boost::shared_ptr<Canvas> canvas);
  QtCanvas(const QtCanvas&) = delete;
  QtCanvas& operator=(const QtCanvas&) = delete;
  virtual ~QtCanvas() noexcept;

  boost::shared_ptr<const Canvas> GetCanvas() const noexcept { return m_canvas; }
  boost::shared_ptr<      Canvas> GetCanvas()       noexcept { return m_canvas; }

  void SetCanvas(const boost::shared_ptr<Canvas> canvas);

  ///Emitted when the QtCanvas is destroyed
  boost::signals2::signal<void()> m_signal_on_destroy;

  virtual void keyPressEvent(QKeyEvent * e) override;
  virtual void keyReleaseEvent(QKeyEvent * e) override;
  virtual void paintEvent(QPaintEvent *) override;

private:
  friend void boost::checked_delete<>(QtCanvas* x);
  friend void boost::checked_delete<>(const QtCanvas* x);

  boost::shared_ptr<Canvas> m_canvas;

  boost::shared_ptr<QImage> m_image; //Used as buffer

  void ShowCanvas(const Canvas * const);
};

} //~namespace ribi

#endif // RIBI_QTCANVAS_H
