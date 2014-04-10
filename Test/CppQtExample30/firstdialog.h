#ifndef FIRSTDIALOG_H
#define FIRSTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class FirstDialog;
}

class FirstDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit FirstDialog(QWidget *parent = 0);
  FirstDialog(const FirstDialog&) = delete;
  FirstDialog& operator=(const FirstDialog&) = delete;
  ~FirstDialog();
    
private:
  Ui::FirstDialog *ui;
};

#endif // FIRSTDIALOG_H
