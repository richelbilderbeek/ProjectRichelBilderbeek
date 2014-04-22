#ifndef QTBRAINSPINNERMAINDIALOG_H
#define QTBRAINSPINNERMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtBrainSpinnerMainDialog;
}

class QtBrainSpinnerMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtBrainSpinnerMainDialog(QWidget *parent = 0);
  ~QtBrainSpinnerMainDialog();

private:
  Ui::QtBrainSpinnerMainDialog *ui;
};

#endif // QTBRAINSPINNERMAINDIALOG_H
