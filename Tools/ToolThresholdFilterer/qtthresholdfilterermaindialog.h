#ifndef QTTHRESHOLDFILTERERMAINDIALOG_H
#define QTTHRESHOLDFILTERERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtThresholdFiltererMainDialog;
}

struct QLabel;

namespace ribi {

class QtThresholdFiltererMainDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtThresholdFiltererMainDialog(QWidget *parent = 0);
  QtThresholdFiltererMainDialog(const QtThresholdFiltererMainDialog&) = delete;
  QtThresholdFiltererMainDialog& operator=(const QtThresholdFiltererMainDialog&) = delete;
  ~QtThresholdFiltererMainDialog() noexcept;

private slots:
  void on_button_load_clicked();
  void on_button_save_clicked();

  void on_pixels_valueChanged(int value);

private:
  Ui::QtThresholdFiltererMainDialog *ui;

  QPixmap * m_source;
  QLabel * m_target;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTTHRESHOLDFILTERERMAINDIALOG_H
