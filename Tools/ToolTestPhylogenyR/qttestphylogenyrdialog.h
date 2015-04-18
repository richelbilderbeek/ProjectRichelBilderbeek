#ifndef QTTESTPHYLOGENYRDIALOG_H
#define QTTESTPHYLOGENYRDIALOG_H

#include <QDialog>

namespace Ui {
class QtTestPhylogenyRdialog;
}

class QtTestPhylogenyRdialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestPhylogenyRdialog(QWidget *parent = 0);
  QtTestPhylogenyRdialog(const QtTestPhylogenyRdialog&) = delete;
  QtTestPhylogenyRdialog& operator=(const QtTestPhylogenyRdialog&) = delete;
  ~QtTestPhylogenyRdialog();

private:
  Ui::QtTestPhylogenyRdialog *ui;
};

#endif // QTTESTPHYLOGENYRDIALOG_H
