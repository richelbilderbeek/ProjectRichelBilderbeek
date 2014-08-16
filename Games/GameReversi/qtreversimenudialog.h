#ifndef QTREVERSIMENUDIALOG_H
#define QTREVERSIMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtReversiMenuDialog;
}

namespace ribi {
namespace reversi {

class QtReversiMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtReversiMenuDialog(QWidget *parent = 0) noexcept;
  QtReversiMenuDialog(const QtReversiMenuDialog&) = delete;
  QtReversiMenuDialog& operator=(const QtReversiMenuDialog&) = delete;
  ~QtReversiMenuDialog() noexcept;
    
private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtReversiMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace reversi
} //~namespace ribi

#endif // QTREVERSIMENUDIALOG_H
