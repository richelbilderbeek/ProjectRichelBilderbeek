#ifndef QTHOMETRAINERMAINDIALOG_H
#define QTHOMETRAINERMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtHometrainerMainDialog;
}

class QtHometrainerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtHometrainerMainDialog(QWidget *parent = 0);
  ~QtHometrainerMainDialog();
  
private:
  Ui::QtHometrainerMainDialog *ui;
};

#endif // QTHOMETRAINERMAINDIALOG_H
