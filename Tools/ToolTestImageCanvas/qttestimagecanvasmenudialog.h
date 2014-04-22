#ifndef QTTESTIMAGECANVASMENUDIALOG_H
#define QTTESTIMAGECANVASMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestImageCanvasMenuDialog;
}

namespace ribi {

class QtTestImageCanvasMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestImageCanvasMenuDialog(QWidget *parent = 0);
  QtTestImageCanvasMenuDialog(const QtTestImageCanvasMenuDialog&) = delete;
  QtTestImageCanvasMenuDialog& operator=(const QtTestImageCanvasMenuDialog&) = delete;
  ~QtTestImageCanvasMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestImageCanvasMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_canvas_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTIMAGECANVASMENUDIALOG_H
