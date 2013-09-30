#ifndef QTTOOLGRAYCODERMENUDIALOG_H
#define QTTOOLGRAYCODERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtGrayCoderMenuDialog;
}

namespace ribi {

class QtGrayCoderMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtGrayCoderMenuDialog(QWidget *parent = 0) noexcept;
  QtGrayCoderMenuDialog(const QtGrayCoderMenuDialog&) = delete;
  QtGrayCoderMenuDialog& operator=(const QtGrayCoderMenuDialog&) = delete;
  ~QtGrayCoderMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtGrayCoderMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLGRAYCODERMENUDIALOG_H
