#ifndef QTTESTMULTICANVASMENUDIALOG_H
#define QTTESTMULTICANVASMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestMultiCanvasMenuDialog;
}

namespace ribi {

class QtTestMultiCanvasMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestMultiCanvasMenuDialog(QWidget *parent = 0);
  QtTestMultiCanvasMenuDialog(const QtTestMultiCanvasMenuDialog&) = delete;
  QtTestMultiCanvasMenuDialog& operator=(const QtTestMultiCanvasMenuDialog&) = delete;
  ~QtTestMultiCanvasMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestMultiCanvasMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_canvas_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTMULTICANVASMENUDIALOG_H
