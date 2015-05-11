#ifndef QTPAPERROCKSCISSORSMENUDIALOG_H
#define QTPAPERROCKSCISSORSMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtPaperRockScissorsMenuDialog;
}

namespace ribi {

class QtPaperRockScissorsMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPaperRockScissorsMenuDialog(QWidget *parent = 0);
  QtPaperRockScissorsMenuDialog(const QtPaperRockScissorsMenuDialog&) = delete;
  QtPaperRockScissorsMenuDialog& operator=(const QtPaperRockScissorsMenuDialog&) = delete;
  ~QtPaperRockScissorsMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtPaperRockScissorsMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTPAPERROCKSCISSORSMENUDIALOG_H
