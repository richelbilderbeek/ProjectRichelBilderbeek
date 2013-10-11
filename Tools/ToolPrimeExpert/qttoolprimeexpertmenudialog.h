#ifndef QTTOOLPRIMEEXPERTMENUDIALOG_H
#define QTTOOLPRIMEEXPERTMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolPrimeExpertMenuDialog;
}

namespace ribi {

class QtToolPrimeExpertMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolPrimeExpertMenuDialog(QWidget *parent = 0);
  QtToolPrimeExpertMenuDialog(const QtToolPrimeExpertMenuDialog&) = delete;
  QtToolPrimeExpertMenuDialog& operator=(const QtToolPrimeExpertMenuDialog&) = delete;
  ~QtToolPrimeExpertMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtToolPrimeExpertMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTTOOLPRIMEEXPERTMENUDIALOG_H
