#ifndef QTDIALOG_H
#define QTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtDialog;
}

struct QStandardItemModel;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private slots:
  void on_button_clicked();

private:
  Ui::QtDialog *ui;
};

#endif // QTDIALOG_H
