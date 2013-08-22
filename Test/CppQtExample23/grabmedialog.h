//---------------------------------------------------------------------------
#ifndef GRABMEDIALOG_H
#define GRABMEDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class GrabMeDialog;
}
//---------------------------------------------------------------------------
class GrabMeDialog : public QDialog
{
  Q_OBJECT

public:
  explicit GrabMeDialog(QWidget *parent = 0);
  ~GrabMeDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::GrabMeDialog *ui;

private slots:
  void on_button_grab_clicked();
};
//---------------------------------------------------------------------------
#endif // GRABMEDIALOG_H
//---------------------------------------------------------------------------
