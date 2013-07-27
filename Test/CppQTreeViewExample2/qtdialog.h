#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>

namespace Ui {
  class QtDialog;
}

struct QStandardItemModel;
struct QUndoStack;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  ~QtDialog();

protected:
  void keyPressEvent(QKeyEvent *);
  
private slots:
  void on_button_clicked();

private:
  Ui::QtDialog *ui;
  QStandardItemModel * const m_model;
  QUndoStack * const m_undo_stack;
};

#endif // QTDIALOG_H
