#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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
};

#endif // DIALOG_H
