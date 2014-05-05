#ifndef DIALOG_H
#define DIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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

private slots:
  void on_pushButton_clicked();

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_H
