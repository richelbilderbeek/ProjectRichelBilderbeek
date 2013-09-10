#ifndef QTSTATEOBSERVERMENUDIALOG_H
#define QTSTATEOBSERVERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtStateObserverMenuDialog;
}

namespace ribi {

class QtStateObserverMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  QtStateObserverMenuDialog(const QtStateObserverMenuDialog&) = delete;
  QtStateObserverMenuDialog& operator=(const QtStateObserverMenuDialog&) = delete;

  explicit QtStateObserverMenuDialog(QWidget *parent = 0);
  ~QtStateObserverMenuDialog();

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtStateObserverMenuDialog *ui;
};

} //~namespace ribi

#endif // QTSTATEOBSERVERMENUDIALOG_H
