#ifndef QTTESTDRAWCANVASMAINDIALOG_H
#define QTTESTDRAWCANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestDrawCanvasMainDialog;
}

namespace ribi {

struct DrawCanvas;
struct QtSurfacePlotWidget;

class QtTestDrawCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestDrawCanvasMainDialog(QWidget *parent = 0);
  QtTestDrawCanvasMainDialog(const QtTestDrawCanvasMainDialog&) = delete;
  QtTestDrawCanvasMainDialog& operator=(const QtTestDrawCanvasMainDialog&) = delete;
  ~QtTestDrawCanvasMainDialog() noexcept;
  
private slots:

  void on_box_color_system_currentIndexChanged(int index);

  void on_box_coordinat_system_currentIndexChanged(int index);

  void on_button_arc_clicked();
  void on_button_circle_clicked();
  void on_button_clear_clicked();
  void on_button_dot_clicked();
  void on_button_ellipse_clicked();
  void on_button_line_clicked();

private:
  Ui::QtTestDrawCanvasMainDialog *ui;
  boost::shared_ptr<DrawCanvas> m_canvas;
  QtSurfacePlotWidget * m_surface_plot;

  static const boost::shared_ptr<DrawCanvas> CreateCanvas();
  void OnChanged() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTDRAWCANVASMAINDIALOG_H
