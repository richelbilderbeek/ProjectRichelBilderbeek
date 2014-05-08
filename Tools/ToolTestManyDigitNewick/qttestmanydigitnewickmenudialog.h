#ifndef QTTESTMANYDIGITNEWICKMENUDIALOG_H
#define QTTESTMANYDIGITNEWICKMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtTestManyDigitNewickMenuDialog;
}

namespace ribi {

class QtTestManyDigitNewickMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtTestManyDigitNewickMenuDialog(QWidget *parent = 0) noexcept;
  QtTestManyDigitNewickMenuDialog(const QtTestManyDigitNewickMenuDialog&) = delete;
  QtTestManyDigitNewickMenuDialog& operator=(const QtTestManyDigitNewickMenuDialog&) = delete;
  ~QtTestManyDigitNewickMenuDialog() noexcept;
    
private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtTestManyDigitNewickMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTMANYDIGITNEWICKMENUDIALOG_H
