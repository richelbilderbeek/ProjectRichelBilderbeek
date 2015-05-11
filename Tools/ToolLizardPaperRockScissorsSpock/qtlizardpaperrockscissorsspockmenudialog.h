#ifndef QTLIZARDPAPERROCKSCISSORSSPOCKMENUDIALOG_H
#define QTLIZARDPAPERROCKSCISSORSSPOCKMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtLizardPaperRockScissorsSpockMenuDialog;
}

namespace ribi {

class QtLizardPaperRockScissorsSpockMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtLizardPaperRockScissorsSpockMenuDialog(QWidget *parent = 0);
  QtLizardPaperRockScissorsSpockMenuDialog(const QtLizardPaperRockScissorsSpockMenuDialog&) = delete;
  QtLizardPaperRockScissorsSpockMenuDialog& operator=(const QtLizardPaperRockScissorsSpockMenuDialog&) = delete;
  ~QtLizardPaperRockScissorsSpockMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtLizardPaperRockScissorsSpockMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTLIZARDPAPERROCKSCISSORSSPOCKMENUDIALOG_H
