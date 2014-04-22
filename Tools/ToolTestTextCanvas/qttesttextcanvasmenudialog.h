#ifndef QTTESTTEXTCANVASMENUDIALOG_H
#define QTTESTTEXTCANVASMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestTextCanvasMenuDialog;
}

namespace ribi {

class QtTestTextCanvasMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTextCanvasMenuDialog(QWidget *parent = 0);
  QtTestTextCanvasMenuDialog(const QtTestTextCanvasMenuDialog&) = delete;
  QtTestTextCanvasMenuDialog& operator=(const QtTestTextCanvasMenuDialog&) = delete;
  ~QtTestTextCanvasMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestTextCanvasMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_canvas_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTEXTCANVASMENUDIALOG_H
