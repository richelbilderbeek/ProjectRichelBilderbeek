#ifndef QTVALENTINECARDDECRYPTERMENUDIALOG_H
#define QTVALENTINECARDDECRYPTERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtValentineCardDecrypterMenuDialog;
}

namespace ribi {

class QtValentineCardDecrypterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtValentineCardDecrypterMenuDialog(QWidget *parent = 0);
  QtValentineCardDecrypterMenuDialog(const QtValentineCardDecrypterMenuDialog&) = delete;
  QtValentineCardDecrypterMenuDialog& operator=(const QtValentineCardDecrypterMenuDialog&) = delete;
  ~QtValentineCardDecrypterMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtValentineCardDecrypterMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTVALENTINECARDDECRYPTERMENUDIALOG_H
