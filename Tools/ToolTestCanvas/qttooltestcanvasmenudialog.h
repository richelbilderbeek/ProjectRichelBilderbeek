#ifndef QTTOOLTESTCANVASMENUDIALOG_H
#define QTTOOLTESTCANVASMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolTestCanvasMenuDialog;
}

class QtToolTestCanvasMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolTestCanvasMenuDialog(QWidget *parent = 0);
  ~QtToolTestCanvasMenuDialog();

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtToolTestCanvasMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  static void Test();
  #endif
};

#endif // QTTOOLTESTCANVASMENUDIALOG_H
