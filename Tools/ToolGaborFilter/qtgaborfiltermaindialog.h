#ifndef QTTOOLGABORFILTERMAINDIALOG_H
#define QTTOOLGABORFILTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolGaborFilterMainDialog;
}

namespace ribi {

class QtToolGaborFilterMainDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtToolGaborFilterMainDialog(QWidget *parent = 0);
  QtToolGaborFilterMainDialog(const QtToolGaborFilterMainDialog&) = delete;
  QtToolGaborFilterMainDialog& operator=(const QtToolGaborFilterMainDialog&) = delete;
  ~QtToolGaborFilterMainDialog() noexcept;
    
private slots:
  void on_dial_angle_sliderMoved(int position) noexcept;
  void on_slider_frequency_sliderMoved(int position) noexcept;
  void on_slider_sigma_sliderMoved(int position) noexcept;

private:
  Ui::QtToolGaborFilterMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLGABORFILTERMAINDIALOG_H
