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
  explicit QtStateObserverMenuDialog(QWidget *parent = 0) noexcept;
  QtStateObserverMenuDialog(const QtStateObserverMenuDialog&) = delete;
  QtStateObserverMenuDialog& operator=(const QtStateObserverMenuDialog&) = delete;
  ~QtStateObserverMenuDialog() noexcept;

private slots:
  void on_button_start_clicked() noexcept;
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;

private:
  Ui::QtStateObserverMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTATEOBSERVERMENUDIALOG_H
