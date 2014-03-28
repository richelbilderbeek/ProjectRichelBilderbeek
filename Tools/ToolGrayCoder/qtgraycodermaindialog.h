#ifndef QTTOOLGRAYCODERMAINDIALOG_H
#define QTTOOLGRAYCODERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtGrayCoderMainDialog;
}

namespace ribi {

class QtGrayCoderMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtGrayCoderMainDialog(QWidget *parent = 0);
  QtGrayCoderMainDialog(const QtGrayCoderMainDialog&) = delete;
  QtGrayCoderMainDialog& operator=(const QtGrayCoderMainDialog&) = delete;
  ~QtGrayCoderMainDialog() noexcept;

private slots:
  void on_box_int_valueChanged(int arg1) noexcept;
  void on_box_gray_valueChanged(int arg1) noexcept;

private:
  Ui::QtGrayCoderMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLGRAYCODERMAINDIALOG_H
