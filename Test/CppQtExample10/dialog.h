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
  ~Dialog();

protected:
  void changeEvent(QEvent *e);
  void resizeEvent(QResizeEvent *e); //Added

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_H
