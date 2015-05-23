#ifndef QTPAPERROCKSCISSORSWITHTRAITMENUDIALOG_H
#define QTPAPERROCKSCISSORSWITHTRAITMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtPaperRockScissorsWithTraitMenuDialog;
}

namespace ribi {

class QtPaperRockScissorsWithTraitMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPaperRockScissorsWithTraitMenuDialog(QWidget *parent = 0);
  QtPaperRockScissorsWithTraitMenuDialog(const QtPaperRockScissorsWithTraitMenuDialog&) = delete;
  QtPaperRockScissorsWithTraitMenuDialog& operator=(const QtPaperRockScissorsWithTraitMenuDialog&) = delete;
  ~QtPaperRockScissorsWithTraitMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtPaperRockScissorsWithTraitMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTPAPERROCKSCISSORSWITHTRAITMENUDIALOG_H
