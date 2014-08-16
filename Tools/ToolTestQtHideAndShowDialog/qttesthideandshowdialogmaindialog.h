#ifndef QTTESTHIDEANDSHOWMAINDIALOG_H
#define QTTESTHIDEANDSHOWMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QDialog>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestHideAndShowMainDialog;
}

class QtTestHideAndShowMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestHideAndShowMainDialog(QWidget *parent = 0);
  QtTestHideAndShowMainDialog(const QtTestHideAndShowMainDialog&) = delete;
  QtTestHideAndShowMainDialog& operator=(const QtTestHideAndShowMainDialog&) = delete;
  ~QtTestHideAndShowMainDialog() noexcept;
  
protected:
  ///Prevents warnings as the one below, appearing when pressing ESC:
  /// X Error: BadWind
  /// ow (invalid Window parameter) 3
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
