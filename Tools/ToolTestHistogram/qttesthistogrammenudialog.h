#ifndef QTTESTHISTOGRAMMENUDIALOG_H
#define QTTESTHISTOGRAMMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtTestHistogramMenuDialog;
}

namespace ribi {

class QtTestHistogramMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestHistogramMenuDialog(QWidget *parent = 0);
  QtTestHistogramMenuDialog(const QtTestHistogramMenuDialog&) = delete;
  QtTestHistogramMenuDialog& operator=(const QtTestHistogramMenuDialog&) = delete;
  ~QtTestHistogramMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestHistogramMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTHISTOGRAMMENUDIALOG_H
