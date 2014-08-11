#ifndef QTTESTMULTICANVASMAINDIALOG_H
#define QTTESTMULTICANVASMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestMultiCanvasMainDialog;
}

namespace ribi {

struct Canvas;
struct DrawCanvas;

class QtTestMultiCanvasMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestMultiCanvasMainDialog(QWidget *parent = 0);
  QtTestMultiCanvasMainDialog(const QtTestMultiCanvasMainDialog&) = delete;
  QtTestMultiCanvasMainDialog& operator=(const QtTestMultiCanvasMainDialog&) = delete;
  ~QtTestMultiCanvasMainDialog() noexcept;
  
private slots:

  //void on_box_color_system_currentIndexChanged(int index);
  //void on_box_coordinat_system_currentIndexChanged(int index);
  //void on_button_dot_clicked();
  //void on_button_clear_clicked();
  //void on_button_circle_clicked();
  //void on_button_line_clicked();

private:
  Ui::QtTestMultiCanvasMainDialog *ui;
  boost::shared_ptr<DrawCanvas> m_canvas;

  static const boost::shared_ptr<DrawCanvas> CreateCanvas();
  void ShowCanvas(const Canvas * const canvas = nullptr);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTMULTICANVASMAINDIALOG_H
