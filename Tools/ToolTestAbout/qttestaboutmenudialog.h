#ifndef QTTESTABOUTMENUDIALOG_H
#define QTTESTABOUTMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestAboutMenuDialog;
}

namespace ribi {

class QtTestAboutMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestAboutMenuDialog(QWidget *parent = 0);
  QtTestAboutMenuDialog(const QtTestAboutMenuDialog&) = delete;
  QtTestAboutMenuDialog& operator=(const QtTestAboutMenuDialog&) = delete;
  ~QtTestAboutMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestAboutMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTABOUTMENUDIALOG_H
