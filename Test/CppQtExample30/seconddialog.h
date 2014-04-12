#ifndef SECONDDIALOG_H
#define SECONDDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class SecondDialog;
}

class SecondDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit SecondDialog(QWidget *parent = 0);
  SecondDialog(const SecondDialog&) = delete;
  SecondDialog& operator=(const SecondDialog&) = delete;
  ~SecondDialog() noexcept;
    
private slots:
  void on_pushButton_clicked();

private:
  Ui::SecondDialog *ui;
};

#endif // SECONDDIALOG_H
