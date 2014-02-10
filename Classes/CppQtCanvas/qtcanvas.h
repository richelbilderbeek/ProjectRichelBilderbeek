#ifndef QTCANVAS_H
#define QTCANVAS_H

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

  const boost::shared_ptr<const Canvas> GetCanvas() const noexcept { return m_canvas; }
  const boost::shared_ptr<      Canvas> GetCanvas()       noexcept { return m_canvas; }

  void SetCanvas(const boost::shared_ptr<Canvas> canvas);

  ///Emitted when the QtCanvas is destroyed
  boost::signals2::signal<void()> m_signal_on_destroy;

  virtual void keyPressEvent(QKeyEvent * e);
  virtual void paintEvent(QPaintEvent *);

private:
  friend void boost::checked_delete<>(QtCanvas* x);
  friend void boost::checked_delete<>(const QtCanvas* x);

  boost::shared_ptr<Canvas> m_canvas;

  boost::shared_ptr<QImage> m_image; //Used as buffer
  //QTimer * const m_resize_timer;

  void ShowCanvas(const Canvas * const);

  //private slots:
  //void OnResizeTimer();

};

} //~namespace ribi

#endif // QTCANVAS_H
