#ifndef QTTESTDRAWCANVASMENUDIALOG_H
#define QTTESTDRAWCANVASMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestDrawCanvasMenuDialog;
}

namespace ribi {

class QtTestDrawCanvasMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestDrawCanvasMenuDialog(QWidget *parent = 0);
  QtTestDrawCanvasMenuDialog(const QtTestDrawCanvasMenuDialog&) = delete;
  QtTestDrawCanvasMenuDialog& operator=(const QtTestDrawCanvasMenuDialog&) = delete;
  ~QtTestDrawCanvasMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestDrawCanvasMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_canvas_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTDRAWCANVASMENUDIALOG_H
