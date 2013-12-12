#ifndef QTTOOLDOTMATRIXMENUDIALOG_H
#define QTTOOLDOTMATRIXMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtDotMatrixMenuDialog;
}

namespace ribi {

class QtDotMatrixMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtDotMatrixMenuDialog(QWidget *parent = 0);
  QtDotMatrixMenuDialog(const QtDotMatrixMenuDialog&) = delete;
  QtDotMatrixMenuDialog& operator=(const QtDotMatrixMenuDialog&) = delete;
  ~QtDotMatrixMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtDotMatrixMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLDOTMATRIXMENUDIALOG_H
