#ifndef QTQUADRATICSOLVERMAINDIALOG_H
#define QTQUADRATICSOLVERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtQuadraticSolverMainDialog;
}

namespace ribi {

class QtQuadraticSolverMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtQuadraticSolverMainDialog(QWidget *parent = 0);
  QtQuadraticSolverMainDialog(const QtQuadraticSolverMainDialog&) = delete;
  QtQuadraticSolverMainDialog& operator=(const QtQuadraticSolverMainDialog&) = delete;
  ~QtQuadraticSolverMainDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtQuadraticSolverMainDialog *ui;

private slots:
  void on_box_a_valueChanged(double arg1);
  void on_box_b_valueChanged(double arg1);
  void on_box_c_valueChanged(double arg1);
  void OnAnyChange();
};

} //~namespace ribi

#endif // QTQUADRATICSOLVERMAINDIALOG_H
