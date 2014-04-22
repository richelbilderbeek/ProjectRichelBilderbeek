#ifndef QTTESTLEDMENUDIALOG_H
#define QTTESTLEDMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestLedMenuDialog;
}

namespace ribi {

class QtTestLedMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestLedMenuDialog(QWidget *parent = 0) noexcept;
  QtTestLedMenuDialog(const QtTestLedMenuDialog&) = delete;
  QtTestLedMenuDialog& operator=(const QtTestLedMenuDialog&) = delete;
  ~QtTestLedMenuDialog() noexcept;

private slots:
  void on_button_start_clicked() noexcept;
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;

private:
  Ui::QtTestLedMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTLEDMENUDIALOG_H
