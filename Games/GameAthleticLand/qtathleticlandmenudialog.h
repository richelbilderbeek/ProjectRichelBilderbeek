#ifndef QTATHLETICLANDMENUDIALOG_H
#define QTATHLETICLANDMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtAthleticLandMenuDialog;
}

namespace ribi {
namespace athl {

class QtAthleticLandMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAthleticLandMenuDialog(QWidget *parent = 0);
  QtAthleticLandMenuDialog(const QtAthleticLandMenuDialog&) = delete;
  QtAthleticLandMenuDialog& operator=(const QtAthleticLandMenuDialog&) = delete;
  ~QtAthleticLandMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtAthleticLandMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace athl
} //~namespace ribi

#endif // QTATHLETICLANDMENUDIALOG_H
