#ifndef QTUBUNTUONEWATCHERMENUDIALOG_H
#define QTUBUNTUONEWATCHERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtUbuntuOneWatcherMenuDialog;
}

namespace ribi {

class QtUbuntuOneWatcherMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtUbuntuOneWatcherMenuDialog(QWidget *parent = 0);
  QtUbuntuOneWatcherMenuDialog(const QtUbuntuOneWatcherMenuDialog&) = delete;
  QtUbuntuOneWatcherMenuDialog& operator=(const QtUbuntuOneWatcherMenuDialog&) = delete;
  ~QtUbuntuOneWatcherMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtUbuntuOneWatcherMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTUBUNTUONEWATCHERMENUDIALOG_H
