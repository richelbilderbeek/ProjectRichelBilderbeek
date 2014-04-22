#ifndef QTTOOLPREDICKADVOCATORMENUDIALOG_H
#define QTTOOLPREDICKADVOCATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPreDickAdvocaTorMenuDialog;
}

namespace ribi {

class QtPreDickAdvocaTorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPreDickAdvocaTorMenuDialog(QWidget *parent = 0);
  QtPreDickAdvocaTorMenuDialog(const QtPreDickAdvocaTorMenuDialog&) = delete;
  QtPreDickAdvocaTorMenuDialog& operator=(const QtPreDickAdvocaTorMenuDialog&) = delete;
  ~QtPreDickAdvocaTorMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtPreDickAdvocaTorMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLPREDICKADVOCATORMENUDIALOG_H
