#ifndef QTPIXELATORMENUDIALOG_H
#define QTPIXELATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPixelatorMenuDialog;
}

namespace ribi {

class QtPixelatorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPixelatorMenuDialog(QWidget *parent = 0);
  QtPixelatorMenuDialog(const QtPixelatorMenuDialog&) = delete;
  QtPixelatorMenuDialog& operator=(const QtPixelatorMenuDialog&) = delete;
  ~QtPixelatorMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtPixelatorMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTPIXELATORMENUDIALOG_H
