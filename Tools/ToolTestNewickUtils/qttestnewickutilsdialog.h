#ifndef QTTESTNEWICKUTILSDIALOG_H
#define QTTESTNEWICKUTILSDIALOG_H

#include <QDialog>

namespace Ui {
class QtTestNewickUtilsdialog;
}

class QtTestNewickUtilsdialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestNewickUtilsdialog(QWidget *parent = 0);
  QtTestNewickUtilsdialog(const QtTestNewickUtilsdialog&) = delete;
  QtTestNewickUtilsdialog& operator=(const QtTestNewickUtilsdialog&) = delete;
  ~QtTestNewickUtilsdialog();

private:
  Ui::QtTestNewickUtilsdialog *ui;
};

#endif // QTTESTNEWICKUTILSDIALOG_H
