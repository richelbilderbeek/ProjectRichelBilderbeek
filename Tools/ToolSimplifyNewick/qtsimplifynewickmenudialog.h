#ifndef QTTOOLSIMPLIFYNEWICKMENUDIALOG_H
#define QTTOOLSIMPLIFYNEWICKMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolSimplifyNewickMenuDialog;
}

namespace ribi {

class QtToolSimplifyNewickMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolSimplifyNewickMenuDialog(QWidget *parent = 0);
  QtToolSimplifyNewickMenuDialog(const QtToolSimplifyNewickMenuDialog&) = delete;
  QtToolSimplifyNewickMenuDialog& operator=(const QtToolSimplifyNewickMenuDialog&) = delete;
  ~QtToolSimplifyNewickMenuDialog() noexcept;

private:
  Ui::QtToolSimplifyNewickMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;
};

} //~namespace ribi

#endif // QTTOOLSIMPLIFYNEWICKMENUDIALOG_H
