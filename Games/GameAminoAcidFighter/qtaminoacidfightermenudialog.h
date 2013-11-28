#ifndef QTAMINOACIDFIGHTERMENUDIALOG_H
#define QTAMINOACIDFIGHTERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtAafMenuDialog;
}

namespace ribi {
namespace aaf {

class QtAafMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAafMenuDialog(QWidget *parent = 0);
  QtAafMenuDialog(const QtAafMenuDialog&) = delete;
  QtAafMenuDialog& operator=(const QtAafMenuDialog&) = delete;
  ~QtAafMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtAafMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace aaf
} //~namespace ribi

#endif // QTAMINOACIDFIGHTERMENUDIALOG_H
