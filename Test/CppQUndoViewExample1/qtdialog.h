#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>

namespace Ui { class QtDialog; }

struct QUndoStack;

class QtDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtDialog(QWidget *parent = 0);
  QtDialog(const QtDialog&) = delete;
  QtDialog& operator=(const QtDialog&) = delete;
  ~QtDialog();
  
private slots:
  void keyPressEvent(QKeyEvent *);
  void on_button_clicked();

private:
  Ui::QtDialog *ui;

  QUndoStack * const m_stack;
};

#endif // QTDIALOG_H
