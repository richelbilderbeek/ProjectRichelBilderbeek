#ifndef QTK3OPEENRIJINSTRUCTIONSDIALOG_H
#define QTK3OPEENRIJINSTRUCTIONSDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtK3OpEenRijInstructionsDialog;
}

namespace ribi {

class QtK3OpEenRijInstructionsDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtK3OpEenRijInstructionsDialog(QWidget *parent = 0) noexcept;
  QtK3OpEenRijInstructionsDialog(const QtK3OpEenRijInstructionsDialog&) = delete;
  QtK3OpEenRijInstructionsDialog& operator=(const QtK3OpEenRijInstructionsDialog&) = delete;
  ~QtK3OpEenRijInstructionsDialog() noexcept;
  
private:
  Ui::QtK3OpEenRijInstructionsDialog *ui;
};

} //~namespace ribi

#endif // QTK3OPEENRIJINSTRUCTIONSDIALOG_H
