#ifndef QTTESTTICTACTOEMENUDIALOG_H
#define QTTESTTICTACTOEMENUDIALOG_H

#include "qthideandshowdialog.h"
#include "tictactoefwd.h"

namespace Ui {
  class QtTestTicTacToeMenuDialog;
}

namespace ribi {
namespace tictactoe {

class QtTestTicTacToeMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTicTacToeMenuDialog(QWidget *parent = 0);
  QtTestTicTacToeMenuDialog(const QtTestTicTacToeMenuDialog&) = delete;
  QtTestTicTacToeMenuDialog& operator=(const QtTestTicTacToeMenuDialog&) = delete;
  ~QtTestTicTacToeMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtTestTicTacToeMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace tictactoe
} //~namespace ribi

#endif // QTTESTTICTACTOEMENUDIALOG_H
