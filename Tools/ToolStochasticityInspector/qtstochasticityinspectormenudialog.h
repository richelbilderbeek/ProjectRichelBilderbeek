#ifndef QTSTOCHASTICITYINSPECTORMENUDIALOG_H
#define QTSTOCHASTICITYINSPECTORMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtStochasticityInspectorMenuDialog;
}

namespace ribi {

class QtStochasticityInspectorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtStochasticityInspectorMenuDialog(QWidget *parent = 0) noexcept;
  QtStochasticityInspectorMenuDialog(const QtStochasticityInspectorMenuDialog&) = delete;
  QtStochasticityInspectorMenuDialog& operator=(const QtStochasticityInspectorMenuDialog&) = delete;
  ~QtStochasticityInspectorMenuDialog() noexcept;

private slots:
  void on_button_start_clicked() noexcept;
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;

private:
  Ui::QtStochasticityInspectorMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTOCHASTICITYINSPECTORMENUDIALOG_H
