#ifndef QTMICROBIALGENETICSLABDIALOG_H
#define QTMICROBIALGENETICSLABDIALOG_H

#include <QDialog>

namespace Ui {
  class QtMicrobialGeneticsLabDialog;
}

class QtMicrobialGeneticsLabDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtMicrobialGeneticsLabDialog(QWidget *parent = 0);
  ~QtMicrobialGeneticsLabDialog();

private:
  Ui::QtMicrobialGeneticsLabDialog *ui;
};

#endif // QTMICROBIALGENETICSLABDIALOG_H
