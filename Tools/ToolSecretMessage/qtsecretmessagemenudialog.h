#ifndef QTSECRETMESSAGEMENUDIALOG_H
#define QTSECRETMESSAGEMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSecretMessageMenuDialog;
}

namespace ribi {

class QtSecretMessageMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtSecretMessageMenuDialog(QWidget *parent = 0);
  QtSecretMessageMenuDialog(const QtSecretMessageMenuDialog&) = delete;
  QtSecretMessageMenuDialog& operator=(const QtSecretMessageMenuDialog&) = delete;
  ~QtSecretMessageMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_create_clicked();
  void on_button_quit_clicked();


  void on_button_extract_clicked();

private:
  Ui::QtSecretMessageMenuDialog *ui;
};

} //~namespace ribi

#endif // QTSECRETMESSAGEMENUDIALOG_H
