#ifndef QTMUTUALISMBREAKDOWNERMENUDIALOG_H
#define QTMUTUALISMBREAKDOWNERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtMutualismBreakdownerMenuDialog;
}

namespace ribi {
namespace mb {

class QtMutualismBreakdownerMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMutualismBreakdownerMenuDialog(QWidget *parent = 0);
  QtMutualismBreakdownerMenuDialog(const QtMutualismBreakdownerMenuDialog&) = delete;
  QtMutualismBreakdownerMenuDialog& operator=(const QtMutualismBreakdownerMenuDialog&) = delete;
  ~QtMutualismBreakdownerMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_time_clicked();
  void on_button_start_spatial_clicked();

private:
  Ui::QtMutualismBreakdownerMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace mb
} //~namespace ribi

#endif // QTMUTUALISMBREAKDOWNERMENUDIALOG_H
