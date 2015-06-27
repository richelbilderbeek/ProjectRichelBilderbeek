#ifndef QTTESTIMAGECANVASMAINDIALOG_H
#define QTTESTIMAGECANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "imagecanvas.h"
#include "canvascolorsystem.h"
#include "canvascoordinatsystem.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestImageCanvasMainDialog;
}

namespace ribi {

struct ImageCanvas;
struct QtCanvas;

class QtTestImageCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestImageCanvasMainDialog(QWidget *parent = 0);
  QtTestImageCanvasMainDialog(const QtTestImageCanvasMainDialog&) = delete;
  QtTestImageCanvasMainDialog& operator=(const QtTestImageCanvasMainDialog&) = delete;
  ~QtTestImageCanvasMainDialog() noexcept;
  
private slots:

  void on_box_color_system_currentIndexChanged(int index);
  void on_box_coordinat_system_currentIndexChanged(int index);
  void on_button_image_clicked();

  void on_box_n_cols_valueChanged(int arg1);

private:
  Ui::QtTestImageCanvasMainDialog *ui;
  ImageCanvas m_canvas;
  QtCanvas * m_qtcanvas;

  static ImageCanvas CreateCanvas();

  CanvasColorSystem GetColorSystem() const noexcept;
  CanvasCoordinatSystem GetCoordinatSystem() const noexcept;
  int GetNcols() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTIMAGECANVASMAINDIALOG_H
