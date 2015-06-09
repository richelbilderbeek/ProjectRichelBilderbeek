#ifndef QTTREESEARCHERMAINDIALOG_H
#define QTTREESEARCHERMAINDIALOG_H

#include <QDialog>

namespace Ui {
class QtTreesearcherMainDialog;
}

class QtTreesearcherMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTreesearcherMainDialog(QWidget *parent = 0);
  ~QtTreesearcherMainDialog();

private:
  Ui::QtTreesearcherMainDialog *ui;
};

#endif // QTTREESEARCHERMAINDIALOG_H
