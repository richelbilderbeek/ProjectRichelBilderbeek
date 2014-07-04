#ifndef QTDIALOG_H
#define QTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class MyDialog;
}

struct MyPlot;

class MyDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MyDialog(QWidget *parent = 0);
  MyDialog(const MyDialog&) = delete;
  MyDialog& operator=(const MyDialog&) = delete;
  ~MyDialog();

  void keyPressEvent(QKeyEvent *);

private:
  Ui::MyDialog *ui;
  MyPlot * const m_plot;
};

#endif // QTDIALOG_H
