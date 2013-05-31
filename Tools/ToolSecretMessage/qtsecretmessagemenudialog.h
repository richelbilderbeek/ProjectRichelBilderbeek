#ifndef QTSECRETMESSAGEMENUDIALOG_H
#define QTSECRETMESSAGEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
class QtSecretMessageMenuDialog;
}
//---------------------------------------------------------------------------
class QtSecretMessageMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtSecretMessageMenuDialog(QWidget *parent = 0);
  ~QtSecretMessageMenuDialog();

private slots:
  void on_button_about_clicked();
  void on_button_create_clicked();
  void on_button_quit_clicked();


  void on_button_extract_clicked();

private:
  Ui::QtSecretMessageMenuDialog *ui;
};
//---------------------------------------------------------------------------
#endif // QTSECRETMESSAGEMENUDIALOG_H
