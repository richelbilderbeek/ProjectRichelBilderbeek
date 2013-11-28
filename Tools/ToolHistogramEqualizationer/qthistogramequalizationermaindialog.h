#ifndef QTTOOLHISTOGRAMEQUALIZATIONERMAINDIALOG_H
#define QTTOOLHISTOGRAMEQUALIZATIONERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtHistogramEqualizationerMainDialog;
}

struct QLabel;

namespace ribi {

class QtHistogramEqualizationerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtHistogramEqualizationerMainDialog(QWidget *parent = 0);
  QtHistogramEqualizationerMainDialog(const QtHistogramEqualizationerMainDialog&) = delete;
  QtHistogramEqualizationerMainDialog& operator=(const QtHistogramEqualizationerMainDialog&) = delete;
  ~QtHistogramEqualizationerMainDialog() noexcept;

private slots:
  void on_button_load_clicked();
  void on_button_save_clicked();

private:
  Ui::QtHistogramEqualizationerMainDialog *ui;
  QLabel * m_target;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLHISTOGRAMEQUALIZATIONERMAINDIALOG_H
