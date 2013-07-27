#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>

namespace Ui {
  class QtDialog;
}

struct QDirModel;
struct QtMyTreeView;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();

protected:
  void keyPressEvent(QKeyEvent *);
  
private slots:

private:
  Ui::QtDialog *ui;
};

#endif // QTDIALOG_H
