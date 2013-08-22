#ifndef SKETCHDIALOG_H
#define SKETCHDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class SketchDialog;
}
//---------------------------------------------------------------------------
class SketchDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SketchDialog(QWidget *parent = 0);
  ~SketchDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::SketchDialog *ui;

private slots:
    void on_button_clear_clicked();
};
//---------------------------------------------------------------------------
#endif // SKETCHDIALOG_H
