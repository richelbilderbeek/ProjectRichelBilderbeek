#ifndef QTSTYLESHEETSETTERMENUDIALOG_H
#define QTSTYLESHEETSETTERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtStyleSheetSetterMenuDialog;
}

namespace ribi {

class QtStyleSheetSetterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtStyleSheetSetterMenuDialog(QWidget *parent = 0);
  QtStyleSheetSetterMenuDialog(const QtStyleSheetSetterMenuDialog&) = delete;
  QtStyleSheetSetterMenuDialog& operator=(const QtStyleSheetSetterMenuDialog&) = delete;
  ~QtStyleSheetSetterMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtStyleSheetSetterMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTYLESHEETSETTERMENUDIALOG_H
