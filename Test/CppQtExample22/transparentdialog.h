#ifndef TRANSPARENTDIALOG_H
#define TRANSPARENTDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class TransparentDialog;
}
//---------------------------------------------------------------------------
class TransparentDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TransparentDialog(QWidget *parent = 0);
  ~TransparentDialog();

protected:
  void changeEvent(QEvent *e);
  void resizeEvent(QResizeEvent *);

private:
  Ui::TransparentDialog *ui;
};
//---------------------------------------------------------------------------
#endif // TRANSPARENTDIALOG_H
