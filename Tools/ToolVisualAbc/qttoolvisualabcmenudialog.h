#ifndef QTTOOLVISUALABCMENUDIALOG_H
#define QTTOOLVISUALABCMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtVisualAbcMenuDialog;
}

namespace ribi {

class QtVisualAbcMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtVisualAbcMenuDialog(QWidget *parent = 0);
  QtVisualAbcMenuDialog(const QtVisualAbcMenuDialog&) = delete;
  QtVisualAbcMenuDialog& operator=(const QtVisualAbcMenuDialog&) = delete;
  ~QtVisualAbcMenuDialog() noexcept;

private:
  Ui::QtVisualAbcMenuDialog *ui;

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLVISUALABCMENUDIALOG_H
