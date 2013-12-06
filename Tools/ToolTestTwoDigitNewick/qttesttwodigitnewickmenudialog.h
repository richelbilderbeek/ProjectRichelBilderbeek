#ifndef QTTESTTWODIGITNEWICKMENUDIALOG_H
#define QTTESTTWODIGITNEWICKMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestTwoDigitNewickMenuDialog;
}

namespace ribi {

class QtTestTwoDigitNewickMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTwoDigitNewickMenuDialog(QWidget *parent = 0);
  QtTestTwoDigitNewickMenuDialog(const QtTestTwoDigitNewickMenuDialog&) = delete;
  QtTestTwoDigitNewickMenuDialog& operator=(const QtTestTwoDigitNewickMenuDialog&) = delete;
  ~QtTestTwoDigitNewickMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtTestTwoDigitNewickMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTWODIGITNEWICKMENUDIALOG_H
