#ifndef QTSEARCHANDDESTROYCHESSGAMEDIALOG_H
#define QTSEARCHANDDESTROYCHESSGAMEDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSearchAndDestroyChessGameDialog;
}

namespace ribi {

class QtSearchAndDestroyChessGameDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSearchAndDestroyChessGameDialog(QWidget *parent = 0);
  QtSearchAndDestroyChessGameDialog(const QtSearchAndDestroyChessGameDialog&) = delete;
  QtSearchAndDestroyChessGameDialog& operator=(const QtSearchAndDestroyChessGameDialog&) = delete;
  ~QtSearchAndDestroyChessGameDialog() noexcept;

private:
  Ui::QtSearchAndDestroyChessGameDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSEARCHANDDESTROYCHESSGAMEDIALOG_H
