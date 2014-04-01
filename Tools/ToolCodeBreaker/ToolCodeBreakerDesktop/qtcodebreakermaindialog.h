#ifndef QTCODEBREAKERMAINDIALOG_H
#define QTCODEBREAKERMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class QtCodeBreakerMainDialog;
}

class QtCodeBreakerMainDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtCodeBreakerMainDialog(QWidget *parent = 0);
  ~QtCodeBreakerMainDialog();
  
private slots:
  void on_lineEdit_2_textEdited(const QString &arg1);

private:
  Ui::QtCodeBreakerMainDialog *ui;
};

#endif // QTCODEBREAKERMAINDIALOG_H
