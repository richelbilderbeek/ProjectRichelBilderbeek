#ifndef QTTOOLHISTOGRAMEQUALIZATIONERMENUDIALOG_H
#define QTTOOLHISTOGRAMEQUALIZATIONERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtHistogramEqualizationerMenuDialog;
}

namespace ribi {

class QtHistogramEqualizationerMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtHistogramEqualizationerMenuDialog(QWidget *parent = 0);
  QtHistogramEqualizationerMenuDialog(const QtHistogramEqualizationerMenuDialog&) = delete;
  QtHistogramEqualizationerMenuDialog& operator=(const QtHistogramEqualizationerMenuDialog&) = delete;
  ~QtHistogramEqualizationerMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtHistogramEqualizationerMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLHISTOGRAMEQUALIZATIONERMENUDIALOG_H
