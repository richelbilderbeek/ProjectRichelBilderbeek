#ifndef QTTOOLGABORFILTERMENUDIALOG_H
#define QTTOOLGABORFILTERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolGaborFilterMenuDialog;
}

namespace ribi {

class QtToolGaborFilterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtToolGaborFilterMenuDialog(QWidget *parent = 0);
  QtToolGaborFilterMenuDialog(const QtToolGaborFilterMenuDialog&) = delete;
  QtToolGaborFilterMenuDialog& operator=(const QtToolGaborFilterMenuDialog&) = delete;
  ~QtToolGaborFilterMenuDialog() noexcept;
    
private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtToolGaborFilterMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLGABORFILTERMENUDIALOG_H
