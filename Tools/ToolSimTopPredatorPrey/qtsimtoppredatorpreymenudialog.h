#ifndef QTSIMTOPPREDATORPREYMENUDIALOG_H
#define QTSIMTOPPREDATORPREYMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSimTopPredatorPreyMenuDialog;
}

namespace ribi {

class QtSimTopPredatorPreyMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSimTopPredatorPreyMenuDialog(QWidget *parent = 0) noexcept;
  QtSimTopPredatorPreyMenuDialog(const QtSimTopPredatorPreyMenuDialog&) = delete;
  QtSimTopPredatorPreyMenuDialog& operator=(const QtSimTopPredatorPreyMenuDialog&) = delete;
  ~QtSimTopPredatorPreyMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtSimTopPredatorPreyMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_tpp_clicked();
  void on_button_start_pp_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSIMTOPPREDATORPREYMENUDIALOG_H
