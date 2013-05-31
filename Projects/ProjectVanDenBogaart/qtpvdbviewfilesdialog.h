#ifndef QTPVDBVIEWFILESDIALOG_H
#define QTPVDBVIEWFILESDIALOG_H

#include <string>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif


namespace Ui { class QtPvdbViewFilesDialog; }

class QtPvdbViewFilesDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbViewFilesDialog(QWidget* parent = 0);
  ~QtPvdbViewFilesDialog();
  
private slots:
  void on_button_left_clicked();
  void keyPressEvent(QKeyEvent* event);
  void OnTimerLeft();
  void OnTimerRight();

  void on_button_right_clicked();

private:
  Ui::QtPvdbViewFilesDialog *ui;
};

#endif // QTPVDBVIEWFILESDIALOG_H
