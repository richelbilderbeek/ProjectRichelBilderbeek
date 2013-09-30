#ifndef QTTOOLDOTMATRIXMAINDIALOG_H
#define QTTOOLDOTMATRIXMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolDotMatrixMainDialog;
}

namespace ribi {

class QtToolDotMatrixMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolDotMatrixMainDialog(QWidget *parent = 0);
  QtToolDotMatrixMainDialog(const QtToolDotMatrixMainDialog&) = delete;
  QtToolDotMatrixMainDialog& operator=(const QtToolDotMatrixMainDialog&) = delete;
  ~QtToolDotMatrixMainDialog() noexcept;

private:
  Ui::QtToolDotMatrixMainDialog *ui;
};

} //~namespace ribi

#endif // QTTOOLDOTMATRIXMAINDIALOG_H
