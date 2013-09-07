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
  ~QtSearchAndDestroyChessGameDialog();

private:
  Ui::QtSearchAndDestroyChessGameDialog *ui;

  static void Test();
};

} //~namespace ribi

#endif // QTSEARCHANDDESTROYCHESSGAMEDIALOG_H
