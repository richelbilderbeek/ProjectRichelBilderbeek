#ifndef QTTESTTOGGLEBUTTONMAINDIALOG_H
#define QTTESTTOGGLEBUTTONMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestToggleButtonMainDialog;
}

namespace ribi {

class QtTestToggleButtonMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestToggleButtonMainDialog(QWidget *parent = 0);
  QtTestToggleButtonMainDialog(const QtTestToggleButtonMainDialog&) = delete;
  QtTestToggleButtonMainDialog& operator=(const QtTestToggleButtonMainDialog&) = delete;
  ~QtTestToggleButtonMainDialog();

protected:


private:
  Ui::QtTestToggleButtonMainDialog *ui;
  void DisplayToggleButtonValue();

private slots:
    void on_dial_dialMoved(int value);
    void OnDial();
    void on_dial_sliderPressed();
};

} //~namespace ribi

#endif // QTTESTTOGGLEBUTTONMAINDIALOG_H
