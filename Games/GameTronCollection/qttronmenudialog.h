#ifndef QTTRONCOLLECTIONMENUDIALOG_H
#define QTTRONCOLLECTIONMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTronMenuDialog;
}

namespace ribi {
namespace tron {

class QtTronMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTronMenuDialog(QWidget *parent = 0);
  QtTronMenuDialog(const QtTronMenuDialog&) = delete;
  QtTronMenuDialog& operator=(const QtTronMenuDialog&) = delete;
  ~QtTronMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtTronMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tron
} //~namespace ribi

#endif // QTTRONCOLLECTIONMENUDIALOG_H
