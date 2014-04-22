#ifndef QTIMAGEROTATERMENUDIALOG_H
#define QTIMAGEROTATERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtImageRotaterMenuDialog;
}

namespace ribi {

class QtImageRotaterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtImageRotaterMenuDialog(QWidget *parent = 0);
  QtImageRotaterMenuDialog(const QtImageRotaterMenuDialog&) = delete;
  QtImageRotaterMenuDialog& operator=(const QtImageRotaterMenuDialog&) = delete;
  ~QtImageRotaterMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtImageRotaterMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTIMAGEROTATERMENUDIALOG_H
