#ifndef DIALOG_H
#define DIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  Dialog(const Dialog&) = delete;
  Dialog& operator=(const Dialog&) = delete;
  ~Dialog();

private:
  Ui::Dialog *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_H
