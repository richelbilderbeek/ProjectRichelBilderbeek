#ifndef QTQUADRATICSOLVERMENUDIALOG_H
#define QTQUADRATICSOLVERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtQuadraticSolverMenuDialog;
}

namespace ribi {

class QtQuadraticSolverMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtQuadraticSolverMenuDialog(QWidget *parent = 0);
  QtQuadraticSolverMenuDialog(const QtQuadraticSolverMenuDialog&) = delete;
  QtQuadraticSolverMenuDialog& operator=(const QtQuadraticSolverMenuDialog&) = delete;
  ~QtQuadraticSolverMenuDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtQuadraticSolverMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTQUADRATICSOLVERMENUDIALOG_H
