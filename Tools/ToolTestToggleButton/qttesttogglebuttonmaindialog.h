#ifndef QTTESTTOGGLEBUTTONMAINDIALOG_H
#define QTTESTTOGGLEBUTTONMAINDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtTestToggleButtonMainDialog;
}
//---------------------------------------------------------------------------
class QtTestToggleButtonMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestToggleButtonMainDialog(QWidget *parent = 0);
  ~QtTestToggleButtonMainDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtTestToggleButtonMainDialog *ui;
  void DisplayToggleButtonValue();

private slots:
    void on_dial_dialMoved(int value);
    void OnDial();
    void on_dial_sliderPressed();
};
//---------------------------------------------------------------------------
#endif // QTTESTTOGGLEBUTTONMAINDIALOG_H
