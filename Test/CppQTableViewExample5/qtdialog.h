#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>

namespace Ui {
  class QtDialog;
}

struct MyModel;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();
  
private slots:

private:
  Ui::QtDialog *ui;

  ///The downcasted model
  MyModel* m_model;
};

#endif // QTDIALOG_H
