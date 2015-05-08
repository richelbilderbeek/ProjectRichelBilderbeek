#ifndef QTMUTUALISMBREAKDOWNERMENUDIALOG_H
#define QTMUTUALISMBREAKDOWNERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtSumBrownianMotionsMenuDialog;
}

namespace ribi {

class QtSumBrownianMotionsMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSumBrownianMotionsMenuDialog(QWidget *parent = 0);
  QtSumBrownianMotionsMenuDialog(const QtSumBrownianMotionsMenuDialog&) = delete;
  QtSumBrownianMotionsMenuDialog& operator=(const QtSumBrownianMotionsMenuDialog&) = delete;
  ~QtSumBrownianMotionsMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtSumBrownianMotionsMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTMUTUALISMBREAKDOWNERMENUDIALOG_H
