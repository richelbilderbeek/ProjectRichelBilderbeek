#ifndef QTTESTBINARYNEWICKVECTORMENUDIALOG_H
#define QTTESTBINARYNEWICKVECTORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestBinaryNewickVectorMenuDialog;
}

namespace ribi {

class QtTestBinaryNewickVectorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestBinaryNewickVectorMenuDialog(QWidget *parent = 0);
  QtTestBinaryNewickVectorMenuDialog(const QtTestBinaryNewickVectorMenuDialog&) = delete;
  QtTestBinaryNewickVectorMenuDialog& operator=(const QtTestBinaryNewickVectorMenuDialog&) = delete;
  ~QtTestBinaryNewickVectorMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtTestBinaryNewickVectorMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTBINARYNEWICKVECTORMENUDIALOG_H
