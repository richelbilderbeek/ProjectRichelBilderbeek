#ifndef QTTHRESHOLDFILTERERMENUDIALOG_H
#define QTTHRESHOLDFILTERERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtThresholdFiltererMenuDialog;
}

namespace ribi {

class QtThresholdFiltererMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtThresholdFiltererMenuDialog(QWidget *parent = 0);
  QtThresholdFiltererMenuDialog(const QtThresholdFiltererMenuDialog&) = delete;
  QtThresholdFiltererMenuDialog& operator=(const QtThresholdFiltererMenuDialog&) = delete;
  ~QtThresholdFiltererMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtThresholdFiltererMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTHRESHOLDFILTERERMENUDIALOG_H
