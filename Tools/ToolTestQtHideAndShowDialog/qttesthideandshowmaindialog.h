#ifndef QTTESTHIDEANDSHOWMAINDIALOG_H
#define QTTESTHIDEANDSHOWMAINDIALOG_H

#include <QDialog>
#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestHideAndShowMainDialog;
}

class QtTestHideAndShowMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestHideAndShowMainDialog(QWidget *parent = 0);
  ~QtTestHideAndShowMainDialog();
  
protected:
  ///Prevents warnings as the one below, appearing when pressing ESC:
  /// X Error: BadWindow (invalid Window parameter) 3
  ///   Major opcode: 20 (X_GetProperty)
  ///   Resource id:  0x280c90d
  /// X Error: BadWindow (invalid Window parameter) 3
  ///   Major opcode: 15 (X_QueryTree)
  ///   Resource id:  0x280c90d
  void keyPressEvent(QKeyEvent *);

  void showEvent(QShowEvent *);

private slots:
  void on_button_clicked();


private:
  Ui::QtTestHideAndShowMainDialog *ui;
};

#endif // QTTESTHIDEANDSHOWMAINDIALOG_H
