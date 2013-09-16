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

  explicit QtStateObserverMenuDialog(QWidget *parent = 0) noexcept;
  ~QtStateObserverMenuDialog() noexcept;

private slots:
  void on_button_start_clicked() noexcept;
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;

private:
  Ui::QtStateObserverMenuDialog *ui;
};

} //~namespace ribi

#endif // QTSTATEOBSERVERMENUDIALOG_H
