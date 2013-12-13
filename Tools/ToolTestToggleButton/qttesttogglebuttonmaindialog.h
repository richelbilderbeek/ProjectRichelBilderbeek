#ifndef QTTESTTOGGLEBUTTONMAINDIALOG_H
#define QTTESTTOGGLEBUTTONMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestToggleButtonMainDialog;
}

namespace ribi {

class QtTestToggleButtonMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestToggleButtonMainDialog(QWidget *parent = 0);
  QtTestToggleButtonMainDialog(const QtTestToggleButtonMainDialog&) = delete;
  QtTestToggleButtonMainDialog& operator=(const QtTestToggleButtonMainDialog&) = delete;
  ~QtTestToggleButtonMainDialog() noexcept;

protected:


private:
  Ui::QtTestToggleButtonMainDialog *ui;
  void DisplayToggleButtonValue();

private slots:
  void on_dial_dialMoved(int value);
  void OnDial();
  void on_dial_sliderPressed();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTTOGGLEBUTTONMAINDIALOG_H
