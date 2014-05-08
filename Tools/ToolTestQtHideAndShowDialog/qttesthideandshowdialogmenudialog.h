#ifndef QTTESTHIDEANDSHOWDIALOGMENUDIALOG_H
#define QTTESTHIDEANDSHOWDIALOGMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestQtHideAndShowDialogMenuDialog;
}

namespace ribi {

class QtTestQtHideAndShowDialogMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQtHideAndShowDialogMenuDialog(QWidget *parent = 0);
  QtTestQtHideAndShowDialogMenuDialog(const QtTestQtHideAndShowDialogMenuDialog&) = delete;
  QtTestQtHideAndShowDialogMenuDialog& operator=(const QtTestQtHideAndShowDialogMenuDialog&) = delete;
  ~QtTestQtHideAndShowDialogMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtTestQtHideAndShowDialogMenuDialog *ui;

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
