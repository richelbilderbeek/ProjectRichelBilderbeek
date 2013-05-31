#ifndef QTPVDBVIEWTESTSDIALOG_H
#define QTPVDBVIEWTESTSDIALOG_H

#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

namespace Ui {
class QtPvdbViewTestsDialog;
}

class QtPvdbViewTestsDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbViewTestsDialog(QWidget* parent = 0);
  ~QtPvdbViewTestsDialog();

protected:
  void keyPressEvent(QKeyEvent* event);
  
private:
  Ui::QtPvdbViewTestsDialog *ui;
};

#endif // QTPVDBVIEWTESTSDIALOG_H
