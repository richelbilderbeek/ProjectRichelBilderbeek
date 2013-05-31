#ifndef QTSEARCHANDDESTROYCHESSGAMEDIALOG_H
#define QTSEARCHANDDESTROYCHESSGAMEDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSearchAndDestroyChessGameDialog;
}

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

#endif // QTSEARCHANDDESTROYCHESSGAMEDIALOG_H
