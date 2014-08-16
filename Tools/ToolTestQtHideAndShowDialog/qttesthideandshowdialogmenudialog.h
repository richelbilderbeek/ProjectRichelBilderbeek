#ifndef QTTESTHIDEANDSHOWDIALOGMENUDIALOG_H
#define QTTESTHIDEANDSHOWDIALOGMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestHideAndShowDialogMenuDialog;
}

namespace ribi {

class QtTestHideAndShowDialogMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestHideAndShowDialogMenuDialog(QWidget *parent = 0);
  QtTestHideAndShowDialogMenuDialog(const QtTestHideAndShowDialogMenuDialog&) = delete;
  QtTestHideAndShowDialogMenuDialog& operator=(const QtTestHideAndShowDialogMenuDialog&) = delete;
  ~QtTestHideAndShowDialogMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtTestHideAndShowDialogMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTTESTHIDEANDSHOWDIALOGMENUDIALOG_H
