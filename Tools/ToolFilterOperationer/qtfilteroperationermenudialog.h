#ifndef QTFILTEROPERATIONERMENUDIALOG_H
#define QTFILTEROPERATIONERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtFilterOperationerMenuDialog;
}

namespace ribi {

class QtFilterOperationerMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtFilterOperationerMenuDialog(QWidget *parent = 0);
  QtFilterOperationerMenuDialog(const QtFilterOperationerMenuDialog&) = delete;
  QtFilterOperationerMenuDialog& operator=(const QtFilterOperationerMenuDialog&) = delete;
  ~QtFilterOperationerMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtFilterOperationerMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTFILTEROPERATIONERMENUDIALOG_H
