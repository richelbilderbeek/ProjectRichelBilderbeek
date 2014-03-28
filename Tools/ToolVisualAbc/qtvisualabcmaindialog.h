#ifndef QTTOOLVISUALABCMAINDIALOG_H
#define QTTOOLVISUALABCMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtVisualAbcMainDialog;
}

namespace ribi {

class QtVisualAbcMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtVisualAbcMainDialog(QWidget *parent = 0);
  QtVisualAbcMainDialog(const QtVisualAbcMainDialog&) = delete;
  QtVisualAbcMainDialog& operator=(const QtVisualAbcMainDialog&) = delete;
  ~QtVisualAbcMainDialog() noexcept;

private:
  Ui::QtVisualAbcMainDialog *ui;
  void resizeEvent(QResizeEvent *);

private slots:
  void on_label_save_clicked();
  void on_button_play_clicked();
  void on_button_convert_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLVISUALABCMAINDIALOG_H
