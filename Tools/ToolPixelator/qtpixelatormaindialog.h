#ifndef QTPIXELATORMAINDIALOG_H
#define QTPIXELATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPixelatorMainDialog;
}

struct QLabel;

namespace ribi {

class QtPixelatorMainDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtPixelatorMainDialog(QWidget *parent = 0);
  QtPixelatorMainDialog(const QtPixelatorMainDialog&) = delete;
  QtPixelatorMainDialog& operator=(const QtPixelatorMainDialog&) = delete;
  ~QtPixelatorMainDialog() noexcept;

private slots:
  void on_button_load_clicked();
  void on_button_save_clicked();

  void on_pixels_valueChanged(int value);

private:
  Ui::QtPixelatorMainDialog *ui;

  QPixmap * m_source;
  QLabel * m_target;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTPIXELATORMAINDIALOG_H
