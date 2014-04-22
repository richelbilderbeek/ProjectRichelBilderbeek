#ifndef QTSEARCHANDDESTROYCHESSMENUDIALOG_H
#define QTSEARCHANDDESTROYCHESSMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSearchAndDestroyChessMenuDialog;
}

namespace ribi {
namespace sadc {

class QtSearchAndDestroyChessMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSearchAndDestroyChessMenuDialog(QWidget *parent = 0);
  QtSearchAndDestroyChessMenuDialog(const QtSearchAndDestroyChessMenuDialog&) = delete;
  QtSearchAndDestroyChessMenuDialog& operator=(const QtSearchAndDestroyChessMenuDialog&) = delete;
  ~QtSearchAndDestroyChessMenuDialog() noexcept;

private:
  Ui::QtSearchAndDestroyChessMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
    void on_button_about_clicked();
    void on_button_start_clicked();
    void on_button_quit_clicked();

};

} //~namespace sadc
} //~namespace ribi

#endif // QTSEARCHANDDESTROYCHESSMENUDIALOG_H
