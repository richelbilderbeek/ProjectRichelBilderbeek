#ifndef QTTESTIMAGECANVASMAINDIALOG_H
#define QTTESTIMAGECANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestImageCanvasMainDialog;
}

namespace ribi {

struct ImageCanvas;

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

  void on_button_dot_clicked();

  void on_button_clear_clicked();

  void on_button_circle_clicked();

  void on_button_line_clicked();

  void on_button_image_clicked();

private:
  Ui::QtTestImageCanvasMainDialog *ui;
  boost::shared_ptr<ImageCanvas> m_canvas;

  static const boost::shared_ptr<ImageCanvas> CreateCanvas();
  void ShowCanvas(const ImageCanvas * const canvas = nullptr);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTIMAGECANVASMAINDIALOG_H
